/*
 * pausemenu.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#include "pausemenu.h"
#include "menubutton.h"
#include "game.h"
#include "camera.h"
#include "graphics.h"
#include "mainmenu.h"

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

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_ESCAPE) ||this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_P) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::start)){
		this->_requestPop = true;
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_UP) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalUp)){
		if(this->_activeButton == 0){
			this->_activeButton = this->_buttonsVector.size() - 1;
		}else{
			this->_activeButton --;
		}
	}
	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_DOWN) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalDown)){
		if(this->_activeButton >= this->_buttonsVector.size() - 1){
			this->_activeButton = 0;
		}else{
			this->_activeButton ++;
		}
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_RIGHT) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalRight)){
		if(this->_activeButton == 0){
			this->_activeButton = this->_buttonsVector.size() - 1;
		}else{
			this->_activeButton --;
		}
	}
	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_LEFT) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalLeft)){
		if(this->_activeButton >= this->_buttonsVector.size() - 1){
			this->_activeButton = 0;
		}else{
			this->_activeButton ++;
		}
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_RETURN) || this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_Z) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::A)){
		this->activateButton();
	}

}

std::string PauseMenu::getMenuType(){
	return "PauseMenu";
}

void PauseMenu::setupButtons(){

	this->_buttonsVector.emplace_back(MenuButton("continue", *this->_graphicsAssociated, 1/3.f, 3/8.f, "assets/PauseMenuButtons.png", 1/3.f, 1/6.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.emplace_back(MenuButton("backToMainMenu", *this->_graphicsAssociated, 1/3.f, 5/8.f, "assets/PauseMenuButtons.png", 1/3.f, 1/6.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 32, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 32, 128, 32, Vector2(0,0));

}

void PauseMenu::activateButton(){

	if(this->_buttonsVector[this->_activeButton].getName() == "continue"){
		this->_requestPop = true;
	}else if(this->_buttonsVector[this->_activeButton].getName() == "backToMainMenu"){
		Game::getInstance().setMenuToReplaceInStack(new MainMenu(*this->_graphicsAssociated, *this->_keyboardInput, *this->_gamepadInput));
		this->_requestPop = true;
	}

}
