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
		AnimatedSprite(graphics, "assets/player.png", 0, 0, player_constants::CONE_WIDTH, player_constants::CONE_HEIGTH, -1000, -1000, 1000),
		_facing(LEFT),
		_dps(100){
	this->setVisible(false);
	this->setupAnimations();
}

void VacuumCone::update(float elapsedTime){

	if(this->getVisible()){

		Vector2 auxColision[4];

		auxColision[0] = Vector2((int)(this->_x/background_blocks_constants::BLOCK_WIDTH), (int)(this->_y/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[1] = Vector2((int)((this->_x + this->_w)/background_blocks_constants::BLOCK_WIDTH), (int)(this->_y/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[2] = Vector2((int)(this->_x/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
		auxColision[3] = Vector2((int)((this->_x + this->_w)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

		// o for a seguir é para o teste caso o cone for menor que o block, no caso ambos atualmente são 64 pixels, mas isso pode mudar

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
