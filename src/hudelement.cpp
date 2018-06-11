/*
 * hudelement.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */


#include "hudelement.h"
#include "game.h"
#include "graphics.h"


HUDElement::HUDElement(){

}

HUDElement::HUDElement(Graphics &graphics, float posRelX, float posRelY, float width, float height, std::string filePath):
		AnimatedSprite(graphics, filePath, 0, 0, width, height, graphics.windowWidth * posRelX, graphics.windowHeight* posRelY, 300)
					{

}

HUDElement::~HUDElement(){

}

void HUDElement::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

std::string HUDElement::getObjectType(){
	return "HUDElement";
}

