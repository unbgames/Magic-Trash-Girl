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

HUDPlayerHp::HUDPlayerHp(Graphics &graphics, Player* associatedPlayer):
		HUDElement(graphics, 0.1f, 0.1f, 0.1f, 0.1f, "assets/hudplayerhp.png"),
		_associatedPlayer(associatedPlayer)
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

	if(this->_associatedPlayer->getHp() >= 4){
		this->playAnimation("HP4");
	}else if(this->_associatedPlayer->getHp() == 3){
		this->playAnimation("HP3");
	}else if(this->_associatedPlayer->getHp() == 2){
		this->playAnimation("HP2");
	}else if(this->_associatedPlayer->getHp() == 1){
		this->playAnimation("HP1");
	}else if(this->_associatedPlayer->getHp() <= 0){
		this->playAnimation("HP0");
	}

	AnimatedSprite::update(elapsedTime);
}

std::string HUDPlayerHp::getObjectType(){
	return "HUDPlayerHp";
}

void HUDPlayerHp::setupAnimations(){
	this->addAnimation(1, 0, 0, "HP4", 128, 131, Vector2(0,0));
	this->addAnimation(1, 0, 131, "HP3", 128, 131, Vector2(0,0));
	this->addAnimation(1, 0, 131*2, "HP2", 128, 131, Vector2(0,0));
	this->addAnimation(1, 0, 131*3, "HP1", 128, 131, Vector2(0,0));
	this->addAnimation(1, 0, 131*4, "HP0", 128, 131, Vector2(0,0));
}

