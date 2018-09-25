/*
 * fullmapbackground.cpp
 *
 *  Created on: Jul 8, 2018
 *      Author: TMK
 */

#include "fullmapbackground.h"

FullMapBackground::FullMapBackground(){

}

FullMapBackground::FullMapBackground(Graphics &graphics, std::string filepath, int width, int height, float posX, float posY):
		AnimatedSprite(graphics, filepath, 0, 0, width, height, posX, posY, 300)
		{

		this->setupAnimations();
		this->playAnimation("IDLE");

}

FullMapBackground::~FullMapBackground(){

}

void FullMapBackground::setupAnimations(){

	this->addAnimation(1, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));

}

std::string FullMapBackground::getObjectType(){
	return "FullMapBackground";
}





