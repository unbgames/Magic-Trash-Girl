/*
 * player.cpp
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#include "player.h"
#include "graphics.h"
#include <iostream>
#include "Game.h"
#include "playerprojectile.h"

Player::Player(){ // @suppress("Class members should be properly initialized")

}

Player::Player(Graphics &graphics, float posX, float posY):
		AnimatedSprite(graphics, "assets/player.png", 0, 0, player_constants::PLAYER_WIDTH, player_constants::PLAYER_HEIGTH, posX, posY, 300),
		_dx(0),
		_dy(0),
		_facing(RIGHT),
		_idleFacing(RIGHT),
		_isAirborne(false),
		_startJump(false),
		_vCone(graphics)
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
	this->addAnimation(2, 0, 0, "IdleLeft", 64,64, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(2, 0, 128, "MoveRight", 64,64, Vector2 (0,0));
	this->addAnimation(2, 0, 128, "MoveLeft", 64,64, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(1, 0, 256, "LookUp", 64,64, Vector2 (0,0));
	this->addAnimation(1, 64, 256, "LookDown", 64,64, Vector2 (0,0));

}

void Player::moveLeft(){
	if(!this->_isAirborne){
		this->_facing = LEFT;
		this->_idleFacing = LEFT;
		this->_dx = -player_constants::WALK_SPEED;
		this->playAnimation("MoveLeft");
	}
}

void Player::moveRight(){
	if(!this->_isAirborne){
		this->_facing = RIGHT;
		this->_idleFacing = RIGHT;
		this->_dx = player_constants::WALK_SPEED;
		this->playAnimation("MoveRight");
	}
}

void Player::stopMoving(){
	if(!this->_isAirborne){
		this->_dx = 0.0f;
		if((this->_facing == UP) || (this->_facing == DOWN)){
			this->_facing = this->_idleFacing;
		}
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
	}
}

void Player::jump(){
	if(!this->_isAirborne){
		this->_startJump = true;
		this->_dy = -0.7;
	}
}

void Player::lookUp(){
	if(!this->_isAirborne){

		this->stopMoving();

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = UP;
		this->playAnimation("LookUp");
	}
}

void Player::lookDown(){
	if(!this->_isAirborne){

		this->stopMoving();

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = DOWN;
		this->playAnimation("LookDown");
	}
}

void Player::bubble(){

	Game::getInstance().addNewSpriteToDraw(new PlayerProjectile(*this->_graphicsAssociated, this->_x - 12 + this->_w/2, this->_y - 12 + this->_h/2, this->_facing));

}

void Player::startVacuum(){

	this->_vCone.setVisible(true);

}

void Player::stopVacuum(){

	this->_vCone.setPosition(-1000, -1000);

	this->_vCone.setVisible(false);

}


void Player::update(float elapsedTime){

	std::cout << "novo frame ---------" << std::endl;

	if(this->_startJump){
		this->_isAirborne = true;
		this->_startJump = false;
	}

	/*
	 * A parte de teste sobre airborne está aqui para setar o chão enquanto não ha teste de colisao, retirar depois
	 */
	if(this->_isAirborne){
		this->_dy += 0.002 * elapsedTime;
		if(this->_y > player_constants::PLAYER_START_Y){
			this->_y = player_constants::PLAYER_START_Y;
			this->_dy = 0;
			this->_isAirborne = false;
		}
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	bool noColision = true;
	int framesInColision = 0;

	do{
		noColision = true;
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
			if((Game::getInstance().getBlockType(auxColision[i].x, auxColision[i].y)) != NONE){
				std::cout << "ocorreu colision no canto " << i << std::endl;

				if(i == 2 || i == 3){
					this->_isAirborne = false;
					noColision = false;
					this->_dy = 0;
					this->_y --;
				}
			}
		}

		if(!noColision){
			framesInColision++;
		}else{
			framesInColision = 0;
		}
	}while(!noColision && framesInColision < 1000);

	if(framesInColision >= 1000){
		std::cout << "game deu crash, player nao conseguiu achar local sem colisao em 1000 tentativas";
		Game::getInstance().requestQuit();
		return;
	}

	if(this->_vCone.getVisible()){
		switch(this->_facing){
			case UP:
				this->_vCone.setPosition(this->_x , this->_y - 32);
				this->_vCone.playAnimation("facingUp");
			break;
			case DOWN:
				this->_vCone.setPosition(this->_x , this->_y + 32);
				this->_vCone.playAnimation("facingDown");
			break;
			case LEFT:
				this->_vCone.setPosition(this->_x - 32, this->_y);
				this->_vCone.playAnimation("facingLeft");
			break;
			case RIGHT:
				this->_vCone.setPosition(this->_x + 32, this->_y);
				this->_vCone.playAnimation("facingRight");
			break;
		}
		this->_vCone.update(elapsedTime);
	}

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics){
	AnimatedSprite::draw(graphics);
	this->_vCone.draw(graphics);
}

void Player::setTimeForFrames(double newTime){
	this->_timeToUpdate = newTime;
}
double Player::getTimeForFrames(){
	return this->_timeToUpdate;
}
