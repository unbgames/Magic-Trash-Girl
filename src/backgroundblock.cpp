/*
 * backgroundblock.cpp
 *
 *  Created on: May 21, 2018
 *      Author: TMK
 */


#include "backgroundblock.h"



BackgroundBlock::BackgroundBlock(Graphics &graphics, int indexX, int indexY, BlockType typeIn):
			AnimatedSprite(graphics, "assets/backgroundblock.png", 0, 0, 64, 64, indexX*background_blocks_constants::BLOCK_WIDTH, indexY*background_blocks_constants::BLOCK_HEIGTH, 300),
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
				case BUBLE:
					this->setVisible(true);
					this->playAnimation("BUBLE");
				break;
			}
}

BackgroundBlock::~BackgroundBlock(){

}

void BackgroundBlock::update(float elapsedTime){

	if(this->_hp <= 0){
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
		case BUBLE:
			this->setVisible(true);
			this->playAnimation("BUBLE");
		break;
	}

	if(this->_hp <= 50){
		switch(this->_type){
			case NONE:
			break;
			case BREAKABLE:
				this->playAnimation("BREAKABLE 50");
			break;
			case UNBREAKABLE:
			break;
			case BUBLE:
				this->playAnimation("BUBLE 50");
			break;
		}
	}

	AnimatedSprite::update(elapsedTime);

}

void BackgroundBlock::setupAnimations(){
	this->addAnimation(1, 0, 192, "NONE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 0, "BREAKABLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 0, "BREAKABLE 50", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 64, "UNBREAKABLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 128, "BUBLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 128, "BUBLE 50", 64,64, Vector2 (0,0));
}

void BackgroundBlock::takeDamage(float damage){
	this->_hp -= damage;
}

BlockType BackgroundBlock::getType(){
	return this->_type;
}

void  BackgroundBlock::setType(BlockType type){
	this->_type = type;
	this->_hp = 100;
}

std::string BackgroundBlock::getObjectType(){
	return "BackgroundBlock";
}
