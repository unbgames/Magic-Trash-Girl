/*
 * portal.cpp
 *
 *  Created on: May 26, 2018
 *      Author: TMK
 */


#include "portal.h"

Portal::Portal(Graphics &graphics, float posX, float posY):
		AnimatedSprite(graphics, "assets/portal.png", 0, 0, background_blocks_constants::BLOCK_WIDTH, background_blocks_constants::BLOCK_HEIGTH, posX, posY, 300)
		{
		this->setupAnimations();
		this->playAnimation("IDLE");
}

Portal::~Portal(){

}

void Portal::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

void Portal::setupAnimations(){
	this->addAnimation(1, 0, 0, "IDLE", 64, 64, Vector2(0,0));
	this->addAnimation(4, 0, 0, "OPEN", 64, 64, Vector2(0,0));
}
