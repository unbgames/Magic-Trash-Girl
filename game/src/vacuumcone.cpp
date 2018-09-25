/*
 * vacuumcone.cpp
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */

#include "vacuumcone.h"
#include "game.h"
#include "config.h"

VacuumCone::VacuumCone(){ // @suppress("Class members should be properly initialized")

}

VacuumCone::VacuumCone(Graphics &graphics):
		AnimatedSprite(graphics, ASSETS_PATH("/vaccum.png"), 0, 0, player_constants::CONE_WIDTH, player_constants::CONE_HEIGTH, -1000, -1000, 100),
		_facing(LEFT),
		_dps(100),
		_isActive(false){
	this->setVisible(false);
	this->setupAnimations();
}

void VacuumCone::update(float elapsedTime){

	if(this->_isActive){

		this->setVisible(true);

		Vector2 auxColision[4];

		/*
		 * 0 = top left
		 * 1 = top right
		 * 2 = bot left
		 * 3 = bot right
		 */

		auxColision[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[1] = Vector2((int)(((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[2] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[3] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));

		for(int i = 0; i < 4; i++){
			bool multipleHits = false;
			for(int j = i+1; j < 4; j++){
				if((auxColision[i].x == auxColision[j].x) && (auxColision[i].y == auxColision[j].y)){
					multipleHits = true;

				}
			}
			if(!multipleHits){
				Game::getInstance().damageBlock(auxColision[i].x,auxColision[i].y,this->_dps*elapsedTime/1000);
			}
		}

		this->_isActive = false;

	}else{
		this->setVisible(false);
		this->setPosition(-1300, -1300);
	}

	AnimatedSprite::update(elapsedTime);
}

void VacuumCone::animationDone(std::string currentAnimation){

}

void VacuumCone::setupAnimations(){
	this->addAnimation(6, 0, 0, "facingRight", 24,24, Vector2 (0,0));
	this->addAnimation(6, 0, 0, "facingLeft", 24,24, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(6, 0, 0, "facingUp", 24,24, Vector2 (0,0), ExVariables(270, nullptr, SDL_FLIP_NONE));
	this->addAnimation(6, 0, 0, "facingDown", 24,24, Vector2 (0,0), ExVariables(90, nullptr, SDL_FLIP_NONE));
}

std::string VacuumCone::getObjectType(){
	return "VacuumCone";
}

void VacuumCone::setActive(bool status){
	this->_isActive = status;
}

bool VacuumCone::getActive(){
	return this->_isActive;
}

float VacuumCone::getDps(){
	return this->_dps;
}
