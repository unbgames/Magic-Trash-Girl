/*
 * hudelement.cpp
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */


#include "hudelement.h"
#include "game.h"
#include "graphics.h"


HUDElement::HUDElement(){ // @suppress("Class members should be properly initialized")

}

HUDElement::HUDElement(Graphics &graphics, float posRelX, float posRelY, float relWidth, float relHeight, std::string filePath):
		AnimatedSprite(graphics, filePath, 0, 0, graphics.windowWidth * relWidth, graphics.windowHeight * relHeight, (graphics.windowWidth * posRelX) + graphics.camera.getx(), (graphics.windowHeight* posRelY) + graphics.camera.gety(), 300),
		_posRelX(posRelX),
		_posRelY(posRelY),
		_fullHDWidth(relWidth),
		_fullHDHeight(relHeight)
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

