/*
 * gamepadinput.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "gamepadinput.h"

GamepadInput::GamepadInput():
	_gamePad(nullptr){
}

GamepadInput::~GamepadInput(){
	if(this->_gamePad){
		SDL_GameControllerClose(this->_gamePad);
	}
}

void GamepadInput::initGamepad(){

	if(SDL_NumJoysticks() < 1){
		std::cout << "nenhum gamepad conectado" << std::endl;
	}

	for(int i = 0; i < SDL_NumJoysticks(); i++){
		if(SDL_IsGameController(i)){
			this->_gamePad = SDL_GameControllerOpen(i);
			if(this->_gamePad){
				break;
			}else{
				std::cout << " Há gamepad disponivel mas ocorreu um erro ao tentar abri-lo, gamepad number: " << i << "   ---  erro: " << SDL_GetError() << std::endl;
			}
		}
	}

}
