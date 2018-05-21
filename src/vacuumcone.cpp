/*
 * vacuumcone.cpp
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */

#include "vacuumcone.h"

VacuumCone::VacuumCone(){

}

VacuumCone::VacuumCone(Graphics &graphics):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, 64, 64, -1000, -1000, 200),
		_facing(LEFT){
	this->setVisible(false);
	this->setupAnimations();
}

void VacuumCone::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

void VacuumCone::animationDone(std::string currentAnimation){

}

void VacuumCone::setupAnimations(){
	this->addAnimation(1, 128, 0, "facingRight", 64,64, Vector2 (0,0));
	this->addAnimation(1, 192, 0, "facingLeft", 64,64, Vector2 (0,0));
	this->addAnimation(1, 128, 64, "facingUp", 64,64, Vector2 (0,0), ExVariables(30, nullptr, SDL_FLIP_NONE));
	this->addAnimation(1, 192, 64, "facingDown", 64,64, Vector2 (0,0));
}
