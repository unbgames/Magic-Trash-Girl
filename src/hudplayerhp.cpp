/*
 * hudplayerhp.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */

#include "hudplayerhp.h"
#include "graphics.h"

HUDPlayerHp::HUDPlayerHp(){

}

HUDPlayerHp::HUDPlayerHp(Graphics &graphics):
		HUDElement(graphics, 0.1f, 0.1f, 0.1f, 0.1f, "assets/hudhp.png")
		{
		this->setupAnimations();
		this->playAnimation("HP4");
}

HUDPlayerHp::~HUDPlayerHp(){

}

void HUDPlayerHp::update(float elapsedTime){

	this->_w = this->_graphicsAssociated->windowWidth * this->_relWidth;
	this->_h = this->_graphicsAssociated->windowHeight * this->_relHeight;

	this->_x = (this->_graphicsAssociated->windowWidth * this->_posRelX) + this->_graphicsAssociated->camera.getx();
	this->_y = (this->_graphicsAssociated->windowHeight * this->_posRelY) + this->_graphicsAssociated->camera.gety();

	AnimatedSprite::update(elapsedTime);
}

std::string HUDPlayerHp::getObjectType(){
	return "HUDPlayerHp";
}

void HUDPlayerHp::setupAnimations(){
	this->addAnimation(1, 0, 0, "HP4", 1024, 1024, Vector2(0,0));
}

