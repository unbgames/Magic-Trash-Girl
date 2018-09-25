/*
 * backgroundblock.cpp
 *
 *  Created on: May 21, 2018
 *      Author: TMK
 */


#include "backgroundblock.h"
#include "game.h"
#include "config.h"

BackgroundBlock::BackgroundBlock(Graphics &graphics, int indexX, int indexY, BlockType typeIn):
			AnimatedSprite(graphics, ASSETS_PATH("/backgroundblock.png"), 0, 0, background_blocks_constants::BLOCK_WIDTH, background_blocks_constants::BLOCK_HEIGTH, indexX*background_blocks_constants::BLOCK_WIDTH, indexY*background_blocks_constants::BLOCK_HEIGTH, 300),
			_hp(100),
			_type(typeIn),
			_indexX(indexX),
			_indexY(indexY)
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
				case WATER:
					this->setVisible(true);
					this->playAnimation("WATER");
				break;
				case OUTOFBONDS:
					this->setVisible(true);
					this->playAnimation("OUTOFBONDS");
				break;
			}

}

BackgroundBlock::~BackgroundBlock(){

}

void BackgroundBlock::update(float elapsedTime){

	if(this->_hp <= 0){
		this->setType(NONE);
		Game::getInstance().redoAdjacentsBlocksBorders(this->_indexX, this->_indexY);
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
		case WATER:
			this->setVisible(true);
			this->playAnimation("WATER");
		break;
		case OUTOFBONDS:
			this->setVisible(true);
			this->playAnimation("OUTOFBONDS");
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
			case WATER:
			break;
			case OUTOFBONDS:
			break;
		}
	}

	for (std::vector<BlockBorder>::iterator it = this->_blockBorderVector.begin() ; it != this->_blockBorderVector.end(); ++it){
		 it->update(elapsedTime);
	}

	AnimatedSprite::update(elapsedTime);

}

void BackgroundBlock::draw(Graphics &graphics){

	AnimatedSprite::draw(graphics);

}

void BackgroundBlock::setupAnimations(){
	this->addAnimation(1, 0, 192, "NONE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 0, "BREAKABLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 0, "BREAKABLE 50", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 64, "UNBREAKABLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 64, "OUTOFBONDS", 64,64, Vector2 (0,0));
	this->addAnimation(1, 0, 128, "BUBLE", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 128, "BUBLE 50", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 192, "WATER", 64,64, Vector2 (0,0));
}

void BackgroundBlock::takeDamage(float damage){
	this->_hp -= damage;
}

BlockType BackgroundBlock::getType(){
	return this->_type;
}

void BackgroundBlock::setType(BlockType type){

	this->_type = type;
	this->_hp = 100;
	this->removeBorders();

}

std::string BackgroundBlock::getObjectType(){
	return "BackgroundBlock";
}

void BackgroundBlock::addBorder(Direction facing){
	if(this->_type != NONE && this->_type != BUBLE){
		this->_blockBorderVector.emplace_back(BlockBorder(*this->_graphicsAssociated, *this, facing));
	}
}

void BackgroundBlock::removeBorders(){
	this->_blockBorderVector.clear();
}

void BackgroundBlock::drawBorder(){
	for (std::vector<BlockBorder>::iterator it = this->_blockBorderVector.begin() ; it != this->_blockBorderVector.end(); ++it){
		 it->draw(*this->_graphicsAssociated);
	}
}

