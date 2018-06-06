/*
 * vacuumcleaner.cpp
 *
 *  Created on: Jun 6, 2018
 *      Author: TMK
 */


#include <vacuumcleaner.h>

VacuumCleaner::VacuumCleaner(){ // @suppress("Class members should be properly initialized")

}

VacuumCleaner::VacuumCleaner(Graphics &graphics, Player &player):
		AnimatedSprite(graphics, "assets/aspirador.png", 0, 0, vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, -1000, -1000, 300),
		_folowingPlayer(true),
		_playerAssociated(&player),
		_facing(RIGHT){

		this->setupAnimations();
		this->playAnimation("IdleRight");

}

VacuumCleaner::~VacuumCleaner(){

}

void VacuumCleaner::update(float elapsedTime){

	if(this->_folowingPlayer){
		this->_x = this->_playerAssociated->getPosX() + this->_playerAssociated->getW()/2 - this->_w/2;
		this->_y = this->_playerAssociated->getPosY() + this->_playerAssociated->getH()/2 - this->_h/2;

		this->_facing = this->_playerAssociated->getFacing();
	}

	switch(this->_facing){
		case UP:
			this->playAnimation("LookUp");
		break;
		case DOWN:
			this->playAnimation("LookDown");
		break;
		case RIGHT:
			this->playAnimation("IdleRight");
		break;
		case LEFT:
			this->playAnimation("IdleLeft");
		break;
	}

	AnimatedSprite::update(elapsedTime);
}

std::string VacuumCleaner::getObjectType(){
	return "VacuumCleaner";
}

void VacuumCleaner::setupAnimations(){

	this->addAnimation(1, 0, 0, "IdleRight", vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, Vector2(0,0));
	this->addAnimation(1, 0, 0, "IdleLeft", vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, Vector2(0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(1, 0, 0, "LookUp", vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, Vector2(0,0), ExVariables(270, nullptr, SDL_FLIP_NONE));
	this->addAnimation(1, 0, 0, "LookDown", vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, Vector2(0,0), ExVariables(90, nullptr, SDL_FLIP_NONE));

}
