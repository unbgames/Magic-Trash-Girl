/*
 * mainmenu.cpp
 *
 *  Created on: May 29, 2018
 *      Author: TMK
 */

#include "mainmenu.h"
#include "game.h"
#include "camera.h"
#include "graphics.h"

MainMenu::MainMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput):
	Menu(graphics, keyboardInput, gamepadInput),
	_camDesX(200),
	_camDesY(150){
	this->_background = MenuBackground(graphics, globals::INITIAL_SCREEN_WIDTH, globals::INITIAL_SCREEN_HEIGTH, "assets/backgroundmenu.png");
	this->setupButtons();
	this->_graphicsAssociated->camera.folowPlayer = false;
}

MainMenu::~MainMenu(){

	this->_graphicsAssociated->camera.folowPlayer = true;

}

void MainMenu::update(float elapsedTime){

	if((this->_graphicsAssociated->camera.getx() == this->_graphicsAssociated->windowWidth/2) || (this->_graphicsAssociated->camera.getx() == (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth/2)){
		this->_camDesX = -1 * this->_camDesX;
	}

	if((this->_graphicsAssociated->camera.gety() == this->_graphicsAssociated->windowHeight/2) || (this->_graphicsAssociated->camera.gety() == (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight/2)){
		this->_camDesY = -1 * this->_camDesY;
	}

	this->_graphicsAssociated->camera.setx(this->_graphicsAssociated->camera.getx() + this->_camDesX * elapsedTime/1000);
	this->_graphicsAssociated->camera.sety(this->_graphicsAssociated->camera.gety() + this->_camDesY * elapsedTime/1000);

	Menu::update(elapsedTime);

}

void MainMenu::handleEvents(){

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_ESCAPE) ||this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_P) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::start)){
		Game::getInstance().requestQuit();
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

std::string MainMenu::getMenuType(){
	return "MainMenu";
}

void MainMenu::setupButtons(){

	this->_buttonsVector.emplace_back(MenuButton("startGame", *this->_graphicsAssociated, 1/3.f, 1/5.f, "assets/MainMenuButtons.png", 1/3.f, 1/5.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.emplace_back(MenuButton("quitGame", *this->_graphicsAssociated, 1/3.f, 3/5.f, "assets/MainMenuButtons.png", 1/3.f, 1/5.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 32, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 0, 32, 128, 32, Vector2(0,0));

}

void MainMenu::activateButton(){

	if(this->_buttonsVector[this->_activeButton].getName() == "startGame"){
		Game::getInstance().createNewPseudoRandomBlocksVector(background_blocks_constants::NUMBER_SECTORS_LINE, background_blocks_constants::NUMBER_SECTORS_COLUMN);
		this->_requestPop = true;
	}else if(this->_buttonsVector[this->_activeButton].getName() == "quitGame"){
		Game::getInstance().requestQuit();
	}

}
