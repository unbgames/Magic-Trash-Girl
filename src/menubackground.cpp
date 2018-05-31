/*
 * menubackground.cpp
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */


#include "menubackground.h"
#include "graphics.h"

MenuBackground::MenuBackground(){ // @suppress("Class members should be properly initialized")

}

MenuBackground::MenuBackground(Graphics &graphics, int width, int height, std::string filepath):
		AnimatedSprite(graphics, filepath, 0, 0, width, height, 0, 0, 300),
		_defaultWidth(width),
		_defaultHeight(height)
		{
		this->setupAnimations();
		this->playAnimation("IDLE");
}

MenuBackground::~MenuBackground(){

}

void MenuBackground::update(float elapsedTime){

	if(this->_defaultWidth > this->_graphicsAssociated->windowWidth){
		this->_w = this->_graphicsAssociated->windowWidth;
	}else{
		this->_w = this->_defaultWidth;
	}

	if(this->_defaultHeight > this->_graphicsAssociated->windowHeight){
		this->_h = this->_graphicsAssociated->windowHeight;
	}else{
		this->_h = this->_defaultHeight;
	}

	this->_x = this->_graphicsAssociated->camera.getx() - this->_w/2 + this->_graphicsAssociated->windowWidth/2;

	this->_y =  this->_graphicsAssociated->camera.gety() - this->_h/2 + this->_graphicsAssociated->windowHeight/2;

	AnimatedSprite::update(elapsedTime);
}

void MenuBackground::setupAnimations(){
	this->addAnimation(1, 0, 0, "IDLE", _defaultWidth, _defaultHeight, Vector2(0,0));
}

std::string MenuBackground::getObjectType(){
	return "MenuBackground";
}
