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
#include "config.h"

MainMenu::MainMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput):
	Menu(graphics, keyboardInput, gamepadInput),
	_camDesX(200),
	_camDesY(150){
	this->_background = MenuBackground(graphics, globals::INITIAL_SCREEN_WIDTH, globals::INITIAL_SCREEN_HEIGTH, ASSETS_PATH("/backgroundmenu.png"));
	this->setupButtons();
	this->_graphicsAssociated->camera.folowPlayer = false;

	click = new Sound(sound_paths::HUD,(unsigned int)24);
	if (click == nullptr) printf ("Não foi possível carregar o som em %s\n", sound_paths::HUD.c_str());

}

MainMenu::~MainMenu(){

	this->_graphicsAssociated->camera.folowPlayer = true;
	delete click;

}

void MainMenu::update(float elapsedTime){
	Game::getInstance().CheckMenuIntro();
	if((this->_graphicsAssociated->camera.getx() == 0) || (this->_graphicsAssociated->camera.getx() == (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth)){
		this->_camDesX = -1 * this->_camDesX;
	}

	if((this->_graphicsAssociated->camera.gety() == 0) || (this->_graphicsAssociated->camera.gety() == (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight)){
		this->_camDesY = -1 * this->_camDesY;
	}

	this->_graphicsAssociated->camera.hardSetX(this->_graphicsAssociated->camera.getx() + this->_camDesX * elapsedTime/1000);
	this->_graphicsAssociated->camera.hardSetY(this->_graphicsAssociated->camera.gety() + this->_camDesY * elapsedTime/1000);

	Menu::update(elapsedTime);

}

void MainMenu::handleEvents(){

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_ESCAPE) ||this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_P) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::start)){
		click->Play(1);
		Game::getInstance().requestQuit();
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_UP) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalUp)){
		click->Play(1);
		if(this->_activeButton == 0){
			this->_activeButton = this->_buttonsVector.size() - 1;
		}else{
			this->_activeButton --;
		}
	}
	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_DOWN) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalDown)){
		click->Play(1);
		if(this->_activeButton >= this->_buttonsVector.size() - 1){
			this->_activeButton = 0;
		}else{
			this->_activeButton ++;
		}
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_RIGHT) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalRight)){
		click->Play(1);
		if(this->_activeButton == 0){
			this->_activeButton = this->_buttonsVector.size() - 1;
		}else{
			this->_activeButton --;
		}
	}
	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_LEFT) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::directionalLeft)){
		click->Play(1);
		if(this->_activeButton >= this->_buttonsVector.size() - 1){
			this->_activeButton = 0;
		}else{
			this->_activeButton ++;
		}
	}

	if(this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_RETURN) || this->_keyboardInput->wasKeyPressed(SDL_SCANCODE_Z) || this->_gamepadInput->wasbuttonPressed(xbox360GamepadMaping::A)){
		click->Play(1);
		this->activateButton();
	}

}

std::string MainMenu::getMenuType(){
	return "MainMenu";
}

void MainMenu::setupButtons(){

	this->_buttonsVector.emplace_back(MenuButton("startGame", *this->_graphicsAssociated, 1/3.f, 3/8.f, ASSETS_PATH("/MainMenuButtons.png"), 1/3.f, 1/8.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 0, 128, 32, Vector2(0,0));

	this->_buttonsVector.emplace_back(MenuButton("quitGame", *this->_graphicsAssociated, 1/3.f, 4/8.f, ASSETS_PATH("/MainMenuButtons.png"), 1/3.f, 1/8.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 32, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 32, 128, 32, Vector2(0,0));

	this->_buttonsVector.emplace_back(MenuButton("tutorial", *this->_graphicsAssociated, 1/3.f, 5 	/8.f, ASSETS_PATH("/MainMenuButtons.png"), 1/3.f, 1/8.f, *this));

	this->_buttonsVector.back().setupIdleAnimation(1, 0, 64, 128, 32, Vector2(0,0));

	this->_buttonsVector.back().setupActiveAnimation(2, 128, 64, 128, 32, Vector2(0,0));

}

void MainMenu::activateButton(){

	if(this->_buttonsVector[this->_activeButton].getName() == "startGame"){
		Game::getInstance().FadeOutMenuMusic();
		Game::getInstance().setupRoomMap();
		this->_requestPop = true;
	}else if(this->_buttonsVector[this->_activeButton].getName() == "quitGame"){
		Game::getInstance().requestQuit();
	}else if(this->_buttonsVector[this->_activeButton].getName() == "tutorial"){
		Game::getInstance().setupTutorialMap();
		this->_requestPop = true;
	}

}
