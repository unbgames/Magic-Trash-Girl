/*
 * menu.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */


#include "menu.h"

Menu::Menu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput):
	_graphicsAssociated(&graphics),
	_keyboardInput(&keyboardInput),
	_gamepadInput(&gamepadInput),
	_requestPop(false){

}

Menu::~Menu(){

}

void Menu::update(float elapsedTime){
	this->_background.update(elapsedTime);

	//iterar pelo vetor de buttons chamando update
}

void Menu::draw(){
	this->_background.draw((*this->_graphicsAssociated));

	//iterar pelo vetor de buttons chamando draw
}

void Menu::addButton(){

}

bool Menu::getRequestPop(){
	return this->_requestPop;
}
