/*
 * backgroundblock.cpp
 *
 *  Created on: May 21, 2018
 *      Author: TMK
 */


#include "backgroundblock.h"



BackgroundBlock::BackgroundBlock(Graphics &graphics, int indexX, int indexY, BlockType typeIn):
			AnimatedSprite(graphics, "assets/player.png", 0, 0, 64, 64, indexX*64, indexY*64, 300),
			_hp(100),
			_type(typeIn)
			{
			this->setupAnimations();
			switch(this->_type){
				case NONE:
					this->setVisible(false);
					this->playAnimation("NONE");
				break;
				case BREAKABLE:
					this->setVisible(true);
					this->playAnimation("BREAKABLE");
				break;
				case UNBREAKABLE:
					this->setVisible(true);
					this->playAnimation("UNBREAKABLE");
				break;
			}
}

BackgroundBlock::~BackgroundBlock(){

}

void BackgroundBlock::update(float elapsedTime){

	if(this->_hp < 0){
		this->_type = NONE;
		this->_hp = 100;
	}

	switch(this->_type){
		case NONE:
			this->setVisible(false);
			this->playAnimation("NONE");
		break;
		case BREAKABLE:
			this->setVisible(true);
			this->playAnimation("BREAKABLE");
		break;
		case UNBREAKABLE:
			this->setVisible(true);
			this->playAnimation("UNBREAKABLE");
		break;
	}

	AnimatedSprite::update(elapsedTime);

}

void BackgroundBlock::setupAnimations(){
	this->addAnimation(1, 192, 0, "NONE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 192, 64, "BREAKABLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 128, 64, "UNBREAKABLE", 64,64, Vector2 (0,0));
}

void BackgroundBlock::takeDamage(float damage){
	this->_hp -= damage;
}

BlockType BackgroundBlock::getType(){
	return this->_type;
}
