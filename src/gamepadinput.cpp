/*
 * gamepadinput.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "gamepadinput.h"
#include "globals.h"

std::vector<SDL_JoystickID> GamepadInput::_gamepadIdUseds;

GamepadInput::GamepadInput(): // @suppress("Class members should be properly initialized")
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
				bool controlerFree = true;
				SDL_JoystickID idAux;
				idAux = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(SDL_GameControllerOpen(i)));
				for (std::vector<SDL_JoystickID>::iterator it = _gamepadIdUseds.begin() ; it != _gamepadIdUseds.end(); ++it){
					if(*it == idAux){
						controlerFree = false;
					}
				}
				if(controlerFree){
					this->_gamepad = SDL_GameControllerOpen(i);
					if(this->_gamepad){
						this->_gamepadId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(this->_gamepad));
						_gamepadIdUseds.push_back(this->_gamepadId);
						std::cout << " gamepad conectado id: " << this->_gamepadId << std::endl;
						break;
					}else{
						std::cout << " Há gamepad disponivel mas ocorreu um erro ao tentar abri-lo, gamepad number: " << i << "   ---  erro: " << SDL_GetError() << std::endl;
					}
				}
			}
		}
	}
}

void GamepadInput::closeGamepad(){
	if(this->_gamepad){
		for (std::vector<SDL_JoystickID>::iterator it = _gamepadIdUseds.begin() ; it != _gamepadIdUseds.end(); ++it){
			if(*it == this->_gamepadId){
				_gamepadIdUseds.erase(it);
				std::cout << "gamepad desconectado id: " << this->_gamepadId << std::endl;;
			}
		}
		SDL_GameControllerClose(this->_gamepad);
		this->_gamepad = nullptr;
		this->_gamepadId = -1;
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

void GamepadInput::clearInputs(){
	this->_pressedButtons.clear();
	this->_releasedButtons.clear();
	this->_heldButtons.clear();
}

SDL_JoystickID GamepadInput::getGamepadId(){
	return this->_gamepadId;
}
