/*
 * player.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#include "player.h"

Player::Player(){ // @suppress("Class members should be properly initialized")

}

Player::Player(Graphics &graphics, float posX, float posY):
		AnimatedSprite(graphics, "assets/test.png", 0, 0, 64, 64, posX, posY, 100),
		_dx(posX),
		_dy(posY),
		_facing(LEFT)
		{}


Player::~Player(){

}

void Player::animationDone(std::string currentAnimation){

}

void Player::setupAnimations(){

}
