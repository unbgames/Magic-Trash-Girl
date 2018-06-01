/*
 * blockborder.cpp
 *
 *  Created on: May 31, 2018
 *      Author: TMK
 */

#include "blockborder.h"
#include "backgroundblock.h"

BlockBorder::BlockBorder(Graphics &graphics, BackgroundBlock blockAssociated):
	AnimatedSprite(graphics, "assets/backgroundblock.png", 0, 0, 80, 80, 0, 0, 300),
	_blockAssociated(&blockAssociated){
	this->_x = this->_blockAssociated->getPosX() - 8;
	this->_y = this->_blockAssociated->getPosY() - 8;
	this->setupAnimations();
	this->playAnimation("IDLE");
}

BlockBorder::~BlockBorder(){

}

void BlockBorder::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

void BlockBorder::setupAnimations(){
	if(this->_blockAssociated->getType() == WATER){
		this->addAnimation(2, 80, 256, "IDLE", 80,80, Vector2 (0,0));
	}else{
		this->addAnimation(1, 0, 256, "IDLE", 80,80, Vector2 (0,0));
	}
}

std::string BlockBorder::getObjectType(){
	return "BlockBorder";
}
