/*
 * pausemenu.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "pausemenu.h"

PauseMenu::PauseMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput):
	Menu(graphics, keyboardInput, gamepadInput){
	this->_background = MenuBackground(graphics, globals::INITIAL_SCREEN_WIDTH, globals::INITIAL_SCREEN_HEIGTH, "assets/backgroundmenu.png");
}

PauseMenu::~PauseMenu(){

}

void PauseMenu::update(float elapsedTime){
	Menu::update(elapsedTime);
}

void PauseMenu::handleEvents(){

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_P) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::start)){
		this->_requestPop = true;
	}

}

std::string PauseMenu::getMenuType(){
	return "PauseMenu";
}

void PauseMenu::setupButtons(){

}
