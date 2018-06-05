/*
 * blockborder.cpp
 *
 *  Created on: May 31, 2018
 *      Author: TMK
 */

#include "blockborder.h"
#include "backgroundblock.h"

BlockBorder::BlockBorder(Graphics &graphics, BackgroundBlock blockAssociated, Direction facing):
	AnimatedSprite(graphics, "assets/backgroundblock.png", 0, 0, 80, 80, 0, 0, 300),
	_blockAssociated(&blockAssociated),
	_facing(facing){

	switch(facing){
		case UP:
			this->_x = this->_blockAssociated->getPosX() - 8;
			this->_y = this->_blockAssociated->getPosY() - 8;
			this->_h = 16;
		break;
		case DOWN:
			this->_x = this->_blockAssociated->getPosX() - 8;
			this->_y = this->_blockAssociated->getPosY() + this->_blockAssociated->getH() - 8;
			this->_h = 16;
		break;
		case RIGHT:
			this->_x = this->_blockAssociated->getPosX() + this->_blockAssociated->getW() - 8;
			this->_y = this->_blockAssociated->getPosY() - 8;
			this->_w = 16;
		break;
		case LEFT:
			this->_x = this->_blockAssociated->getPosX() - 8;
			this->_y = this->_blockAssociated->getPosY() - 8;
			this->_w = 16;
		break;
	}
	this->setupAnimations();
	this->playAnimation("IDLE");

}

BlockBorder::~BlockBorder(){

}

void BlockBorder::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

void BlockBorder::setupAnimations(){

	switch(this->_facing){
		case UP:
			if(this->_blockAssociated->getType() == WATER){
				this->addAnimation(2, 80, 256, "IDLE", 80,16, Vector2 (0,0));
			}else{
				this->addAnimation(1, 0, 256, "IDLE", 80,16, Vector2 (0,0));
			}
		break;
		case DOWN:
			this->addAnimation(1, 0, 320, "IDLE", 80,16, Vector2 (0,0));
		break;
		case RIGHT:
			this->addAnimation(1, 64, 256, "IDLE", 16,80, Vector2 (0,0));
		break;
		case LEFT:
			this->addAnimation(1, 0, 256, "IDLE", 16,80, Vector2 (0,0));
		break;
	}
}

std::string BlockBorder::getObjectType(){
	return "BlockBorder";
}
