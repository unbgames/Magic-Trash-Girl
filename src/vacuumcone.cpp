/*
 * vacuumcone.cpp
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */

#include "vacuumcone.h"

VacuumCone::VacuumCone(Graphics &graphics):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, 24, 24, -1000, -1000, 200),
		_facing(LEFT){
	this->setVisible(false);
	this->setupAnimations();
}

void VacuumCone::update(float elapsedTime){

}

void VacuumCone::animationDone(std::string currentAnimation){

}

void VacuumCone::setupAnimations(){
	this->addAnimation(1, 0, 320, "basic", 24,24, Vector2 (0,0));
}
