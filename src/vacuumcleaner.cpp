/*
 * vacuumcleaner.cpp
 *
 *  Created on: Jun 6, 2018
 *      Author: TMK
 */

#include <vacuumcleaner.h>
#include "game.h"
#include "playerprojectile.h"
#include <cmath>

VacuumCleaner::VacuumCleaner(){ // @suppress("Class members should be properly initialized")

}

VacuumCleaner::VacuumCleaner(Graphics &graphics, Player &player):
		AnimatedSprite(graphics, "assets/aspirador.png", 0, 0, vacuum_constants::VACUUM_WIDTH, vacuum_constants::VACUUM_HEIGTH, -1000, -1000, 300),
		_folowingPlayer(true),
		_playerAssociated(&player),
		_facing(RIGHT),
		_vCone(graphics){

		this->setupAnimations();
		this->playAnimation("IdleRight");

}

VacuumCleaner::~VacuumCleaner(){

}

void VacuumCleaner::moveLeft(){
		this->_facing = LEFT;
		this->_dx = -vacuum_constants::FLOAT_SPEED;

}
void VacuumCleaner::moveRight(){
		this->_facing = RIGHT;
		this->_dx = vacuum_constants::FLOAT_SPEED;
}

void VacuumCleaner::moveUp(){
		this->_facing = UP;
		this->_dy = -vacuum_constants::FLOAT_SPEED;

}
void VacuumCleaner::moveDown(){
		this->_facing = DOWN;
		this->_dy = vacuum_constants::FLOAT_SPEED;
}

void VacuumCleaner::stopMoving(){
		this->_dx = 0.0f;
		this->_dy = 0.0f;
}

void VacuumCleaner::update(float elapsedTime){

	if(this->_folowingPlayer){
		this->_x = this->_playerAssociated->getPosX() + this->_playerAssociated->getW()/2 - this->_w/2;
		this->_y = this->_playerAssociated->getPosY() + this->_playerAssociated->getH()/2 - this->_h/2;

		this->_facing = this->_playerAssociated->getFacing();
	}else{

		this->_x += this->_dx * elapsedTime;
		this->_y += this->_dy * elapsedTime;

		if((this->_x + this->_w/2 - this->_playerAssociated->getPosX() - this->_playerAssociated->getW()/2) > 256){
			this->_x = this->_playerAssociated->getPosX() + this->_playerAssociated->getW()/2 - this->_w/2 + 256;
		}
		if((this->_x + this->_w/2 - this->_playerAssociated->getPosX() - this->_playerAssociated->getW()/2) < -256){
			this->_x = this->_playerAssociated->getPosX() + this->_playerAssociated->getW()/2 - this->_w/2 - 256;
		}
		if((this->_y + this->_h/2 - this->_playerAssociated->getPosY() - this->_playerAssociated->getH()/2) > 256){
			this->_y = this->_playerAssociated->getPosY() + this->_playerAssociated->getH()/2 - this->_h/2 + 256;
		}
		if((this->_y + this->_h/2 - this->_playerAssociated->getPosY() - this->_playerAssociated->getH()/2) < -256){
			this->_y = this->_playerAssociated->getPosY() + this->_playerAssociated->getH()/2 - this->_h/2 - 256;
		}
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

	/*
	 *  calculo de posição do cone
	 */

	// é uma boa passar o calculo da posição do cone para o update dele, fazer isso depois, nem sei pq coloquei o calculo de posição aqui
	if(this->_vCone.getActive()){
		switch(this->_facing){
			case UP:
				//depois arrumar esses valores aqui quando tiver as animaçoes corretas
				this->_vCone.setPosition(this->_x + this->_w/2 - player_constants::CONE_WIDTH/2 , this->_y - this->_w*3/4 - 8);
				this->_vCone.playAnimation("facingUp");
			break;
			case DOWN:
				this->_vCone.setPosition(this->_x + this->_w/2 - player_constants::CONE_WIDTH/2, this->_y + this->_w*3/4);
				this->_vCone.playAnimation("facingDown");
			break;
			case LEFT:
				this->_vCone.setPosition(this->_x - player_constants::CONE_WIDTH, this->_y + this->_h/2 - player_constants::CONE_HEIGTH/2);
				this->_vCone.playAnimation("facingLeft");
			break;
			case RIGHT:
				this->_vCone.setPosition(this->_x + this->_w , this->_y + this->_h/2 - player_constants::CONE_HEIGTH/2);
				this->_vCone.playAnimation("facingRight");
			break;
		}
	}
	this->_vCone.update(elapsedTime);


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

void VacuumCleaner::activateVacuum(){

	this->_vCone.setActive(true);

}

void VacuumCleaner::toggleFolowingPlayer(){
	this->_folowingPlayer = !this->_folowingPlayer;

	if(!this->_folowingPlayer){
		this->stopMoving();
	}
}

void VacuumCleaner::bubble(){

	if(!this->_playerAssociated->getIsSwiming()){
		Game::getInstance().addNewSpriteToDraw(new PlayerProjectile(*this->_graphicsAssociated, this->_x - 12 + this->_w/2, this->_y - 12 + this->_h/2, this->_facing));
	}

}

bool VacuumCleaner::getFolowingPlayer(){
	return this->_folowingPlayer;
}

void VacuumCleaner::draw(Graphics &graphics){
	AnimatedSprite::draw(graphics);
	this->_vCone.draw(graphics);
}

