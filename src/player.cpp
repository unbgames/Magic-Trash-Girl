/*
 * player.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#include "player.h"
#include "graphics.h"
#include <iostream>

Player::Player(){ // @suppress("Class members should be properly initialized")

}

Player::Player(Graphics &graphics, float posX, float posY):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, 64, 64, posX, posY, 200),
		_dx(0),
		_dy(0),
		_facing(RIGHT),
		_isAirborne(false)
		{
			this->setupAnimations();
			this->playAnimation("IdleRight");
		}


Player::~Player(){

}

void Player::animationDone(std::string currentAnimation){

}

void Player::setupAnimations(){
	this->addAnimation(2, 0, 0, "IdleRight", 64,64, Vector2 (0,0));
	this->addAnimation(2, 0, 64, "IdleLeft", 64,64, Vector2 (0,0));
	this->addAnimation(2, 0, 128, "MoveRight", 64,64, Vector2 (0,0));
	this->addAnimation(2, 0, 192, "MoveLeft", 64,64, Vector2 (0,0));
}

void Player::moveLeft(){
	this->_facing = LEFT;
	this->_dx = -player_constants::WALK_SPEED;
	this->playAnimation("MoveLeft");
}

void Player::moveRight(){
	this->_facing = RIGHT;
	this->_dx = player_constants::WALK_SPEED;
	this->playAnimation("MoveRight");
}

void Player::jump(){
	if(!this->_isAirborne){
		this->_isAirborne = true;
		this->_dy = -1.5;
	}
}

void Player::stopMoving(){
	this->_dx = 0.0f;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::update(float elapsedTime){

	/*
	 * A parte de teste sobre airborne está aqui para setar o chão enquanto não ha teste de colisao, retirar depois
	 */
	if(this->_isAirborne){
		this->_dy += 0.002;
		if(this->_y > player_constants::PLAYER_START_Y){
			this->_y = 500;
			this->_dy = 0;
			this->_isAirborne = false;
		}
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}

void Player::setTimeForFrames(double newTime){
	this->_timeToUpdate = newTime;
}
double Player::getTimeForFrames(){
	return this->_timeToUpdate;
}
