/*
 * pausemenu.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "pausemenu.h"
#include "menubutton.h"

PauseMenu::PauseMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput):
	Menu(graphics, keyboardInput, gamepadInput){
	this->_background = MenuBackground(graphics, globals::INITIAL_SCREEN_WIDTH, globals::INITIAL_SCREEN_HEIGTH, "assets/backgroundmenu.png");
	this->setupButtons();

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

	this->_buttonsVector.emplace_back(MenuButton(*this->_graphicsAssociated, 1/3.f, 1/5.f, "assets/PauseMenuButtons.png", 1/3.f, 1/5.f, *this));

	this->_buttonsVector.back().addAnimation(1, 0, 0, "IDLE", 128, 32, Vector2(0,0));

	this->_buttonsVector.back().playAnimation("IDLE");

	this->_buttonsVector.emplace_back(MenuButton(*this->_graphicsAssociated, 1/6.f, 3/5.f, "assets/PauseMenuButtons.png", 2/3.f, 1/5.f, *this));

	this->_buttonsVector.back().addAnimation(1, 0, 32, "IDLE", 256, 32, Vector2(0,0));

	this->_buttonsVector.back().playAnimation("IDLE");


}
