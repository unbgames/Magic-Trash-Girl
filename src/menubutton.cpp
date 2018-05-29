/*
 * menubutton.cpp
 *
 *  Created on: May 29, 2018
 *      Author: TMK
 */

#include "menubutton.h"
#include "menu.h"

/*
 *	MenuButton é derivado de animated sprites, mas é construido por partes
 *	offsets e width são sempre uma fração do tamanho do menu
 */
MenuButton::MenuButton(std::string name, Graphics &graphics, float offsetX, float offsetY, std::string spritesheetPath, float widthFactor, float heightFactor, Menu& menuAssociated):
		AnimatedSprite(graphics, spritesheetPath, 0, 0, 0, 0, -1000, -1000, 300),
		_menuAssociated(&menuAssociated),
		_name(name),
		_offsetX(offsetX),
		_offsetY(offsetY),
		_widthFactor(widthFactor),
		_heightFactor(heightFactor){

}

MenuButton::~MenuButton(){

}

void MenuButton::update(float elapsedTime){

	int auxW, auxH;

	this->_menuAssociated->getPosSize(&this->_x, &this->_y, &auxW, &auxH);

	this->_x += this->_offsetX * auxW;

	this->_y += this->_offsetY * auxH;

	this->_w = this->_widthFactor * auxW;

	this->_h = this->_heightFactor * auxH;

	AnimatedSprite::update(elapsedTime);
}

void MenuButton::setupAnimations(){

}

std::string MenuButton::getObjectType(){
	return "MenuButton";
}

std::string MenuButton::getName(){
	return this->_name;
}

void MenuButton::setupIdleAnimation(int frames, int x, int y, int width, int height, Vector2 offset, ExVariables exVariables){
	this->addAnimation(frames, x, y, "IDLE", width, height, offset, exVariables);
}

void MenuButton::setupActiveAnimation(int frames, int x, int y, int width, int height, Vector2 offset, ExVariables exVariables){
	this->addAnimation(frames, x, y, "ACTIVE", width, height, offset, exVariables);
}
