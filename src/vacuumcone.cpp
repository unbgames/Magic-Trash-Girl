/*
 * vacuumcone.cpp
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */

#include "vacuumcone.h"
#include "game.h"

VacuumCone::VacuumCone(){ // @suppress("Class members should be properly initialized")

}

VacuumCone::VacuumCone(Graphics &graphics):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, 64, 64, -1000, -1000, 1000),
		_facing(LEFT),
		_dps(100){
	this->setVisible(false);
	this->setupAnimations();
}

void VacuumCone::update(float elapsedTime){

	if(this->getVisible()){

		//arrumar test de colision com os blocks aqui, fiz um fudido soh pra test mesmo, ta errado pacas

		int index1X = (int)(this->_x/64);
		int index1Y = (int)(this->_y/64);

		int index2X = (int)((this->_x + this->_w)/64);
		int index2Y = (int)(this->_y/64);

		int index3X = (int)(this->_x/64);
		int index3Y = (int)((this->_y+ this->_h)/64);

		int index4X = (int)((this->_x+ this->_w)/64);
		int index4Y = (int)((this->_y+ this->_h)/64);

		Game::getInstance().damageBlock(index1X,index1Y,this->_dps*elapsedTime/1000);
		Game::getInstance().damageBlock(index2X,index2Y,this->_dps*elapsedTime/1000);
		Game::getInstance().damageBlock(index3X,index3Y,this->_dps*elapsedTime/1000);
		Game::getInstance().damageBlock(index4X,index4Y,this->_dps*elapsedTime/1000);

	}

	AnimatedSprite::update(elapsedTime);
}

void VacuumCone::animationDone(std::string currentAnimation){

}

void VacuumCone::setupAnimations(){
	this->addAnimation(1, 128, 0, "facingRight", 64,64, Vector2 (0,0));
	this->addAnimation(1, 128, 0, "facingLeft", 64,64, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(1, 128, 0, "facingUp", 64,64, Vector2 (0,0), ExVariables(270, nullptr, SDL_FLIP_NONE));
	this->addAnimation(1, 128, 0, "facingDown", 64,64, Vector2 (0,0), ExVariables(90, nullptr, SDL_FLIP_NONE));
}
