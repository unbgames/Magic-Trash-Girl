/*
 * portal.cpp
 *
 *  Created on: May 26, 2018
 *      Author: TMK
 */


#include "portal.h"
#include "game.h"
#include "config.h"

Portal::Portal(Graphics &graphics, float posX, float posY, std::string type, std::string local):
		AnimatedSprite(graphics, ASSETS_PATH("/portal.png"), 0, 0, background_blocks_constants::BLOCK_WIDTH, background_blocks_constants::BLOCK_HEIGTH, posX, posY, 300),
		_type(type),
		_local(local){
		this->setupAnimations();
		this->playAnimation("IDLE");
}

Portal::~Portal(){

}

void Portal::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

void Portal::setupAnimations(){
	if(this->_local == "bathroom"){
		this->addAnimation(1, 0, 64, "IDLE", 64, 64, Vector2(0,0));
		this->addAnimation(4, 0, 64, "OPEN", 64, 64, Vector2(0,0));
	}else{
		this->addAnimation(1, 0, 0, "IDLE", 64, 64, Vector2(0,0));
		this->addAnimation(4, 0, 0, "OPEN", 64, 64, Vector2(0,0));
	}
}

std::string Portal::getObjectType(){
	return "Portal";
}

void Portal::takeContextAction(std::string objectType){

	if(objectType == "Player"){
		this->playAnimation("OPEN", true);
	}

}

void Portal::animationDone(std::string currentAnimation){
	if(currentAnimation == "OPEN"){
		this->_loadAssociatedLevel();
	}
}

//aqui carrega o level associado ao portal, como por enquanto o unico level eh o randomicamente gerado sempre sera ele por enquanto
void Portal::_loadAssociatedLevel(){
	if(this->_type == "pseudoRandomLevel"){
		Game::getInstance().createNewPseudoRandomBlocksVector(background_blocks_constants::NUMBER_SECTORS_LINE, background_blocks_constants::NUMBER_SECTORS_COLUMN);
	}else if(this->_type == "room"){
		Game::getInstance().setupRoomMap();
	}else if(this->_type == "bathroom"){
		Game::getInstance().setupBathroomMap();
	}
}

