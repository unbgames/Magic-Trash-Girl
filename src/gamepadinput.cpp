/*
 * gamepadinput.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "gamepadinput.h"

GamepadInput::GamepadInput():
	_gamepad(nullptr){
}

GamepadInput::~GamepadInput(){
	this->closeGamepad();
}

void GamepadInput::initGamepad(){

	if(!this->_gamepad){
		if(SDL_NumJoysticks() < 1){
			std::cout << "nenhum gamepad conectado" << std::endl;
		}

		for(int i = 0; i < SDL_NumJoysticks(); i++){
			if(SDL_IsGameController(i)){
				this->_gamepad = SDL_GameControllerOpen(i);
				if(this->_gamepad){
					this->_gamepadId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(this->_gamepad));
					std::cout << " gamepad conectado " << std::endl;
					break;
				}else{
					std::cout << " Há gamepad disponivel mas ocorreu um erro ao tentar abri-lo, gamepad number: " << i << "   ---  erro: " << SDL_GetError() << std::endl;
				}
			}
		}
	}
}

void GamepadInput::closeGamepad(){
	if(this->_gamepad){
		SDL_GameControllerClose(this->_gamepad);
		this->_gamepad = nullptr;
		std::cout << " gamepad desconectado " << std::endl;
	}
}

void GamepadInput::beginNewFrame(){
	this->_pressedButtons.clear();
	this->_releasedButtons.clear();
}

void GamepadInput::buttonDownEvent(const SDL_Event& event){
	if(event.cbutton.which == this->_gamepadId){
		this->_pressedButtons[event.cbutton.button] = true;
		this->_heldButtons[event.cbutton.button] = true;
	}
}

void GamepadInput::buttonUpEvent(const SDL_Event& event){
	if(event.cbutton.which == this->_gamepadId){
		this->_releasedButtons[event.cbutton.button] = true;
		this->_heldButtons[event.cbutton.button] = false;
	}
}

bool GamepadInput::wasbuttonPressed(Uint8 button){
	return this->_pressedButtons[button];
}

bool GamepadInput::wasbuttonReleased(Uint8 button){
	return this->_releasedButtons[button];
}

bool GamepadInput::isbuttonHeld(Uint8 button){
	return this->_heldButtons[button];
}
