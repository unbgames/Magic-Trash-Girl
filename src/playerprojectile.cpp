/*
 * playerprojetil.cpp
 *
 *  Created on: May 17, 2018
 *      Author: TMK
 */

#include <playerprojectile.h>
#include <iostream>

PlayerProjectile::PlayerProjectile(Graphics &graphics, float posX, float posY, Direction facing):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, 64, 64, posX, posY, 200),
		_facing(facing){
	this->setupAnimations();
	this->playAnimation("basic");
}

void PlayerProjectile::update(float elapsedTime){

	std::cout << "passou";

	switch(this->_facing){
		case UP:
			this->_y -= player_constants::PROJECTILE_SPEED * elapsedTime;
		break;
		case DOWN:
			this->_y += player_constants::PROJECTILE_SPEED * elapsedTime;
		break;
		case LEFT:
			this->_x -= player_constants::PROJECTILE_SPEED * elapsedTime;
		break;
		case RIGHT:
			this->_x += player_constants::PROJECTILE_SPEED * elapsedTime;
		break;
	}
	AnimatedSprite::update(elapsedTime);
}

void PlayerProjectile::animationDone(std::string currentAnimation){

}

void PlayerProjectile::setupAnimations(){
	this->addAnimation(2, 0, 0, "basic", 64,64, Vector2 (0,0));
}
