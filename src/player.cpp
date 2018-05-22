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
		this->_facing = LEFT;
		this->_idleFacing = LEFT;
		this->_dx = -player_constants::WALK_SPEED;
		this->playAnimation("MoveLeft");
}

void Player::moveRight(){
		this->_facing = RIGHT;
		this->_idleFacing = RIGHT;
		this->_dx = player_constants::WALK_SPEED;
		this->playAnimation("MoveRight");
}

void Player::stopMoving(){
		this->_dx = 0.0f;
		if((this->_facing == UP) || (this->_facing == DOWN)){
			this->_facing = this->_idleFacing;
		}
		this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}

void Player::jump(){
	if(!this->_isAirborne){
		this->_startJump = true;
		this->_dy = -0.7;
	}
}

void Player::lookUp(){
		this->stopMoving();

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = UP;
		this->playAnimation("LookUp");
}

void Player::lookDown(){
		this->stopMoving();

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = DOWN;
		this->playAnimation("LookDown");
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

	Vector2 auxCheckAirborne[2];

	auxCheckAirborne[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
	auxCheckAirborne[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

	if(((Game::getInstance().getBlockType(auxCheckAirborne[0].x, auxCheckAirborne[0].y)) == NONE) && ((Game::getInstance().getBlockType(auxCheckAirborne[1].x, auxCheckAirborne[1].y)) == NONE)){
		this->_isAirborne = true;

	}

	if(this->_startJump){
		this->_isAirborne = true;
		this->_startJump = false;
	}

	/*
	 * A parte de teste sobre airborne está aqui para setar o chão enquanto não ha teste de colisao, retirar depois
	 */
	if(this->_isAirborne){
		this->_dy += 0.002 * elapsedTime;
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	bool noColision = true;
	int framesInColision = 0;
	bool checkAirborne = false;

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

		bool colisionArray[4] = {false,false,false,false};

		for(int i = 0; i < 4; i++){
			if((Game::getInstance().getBlockType(auxColision[i].x, auxColision[i].y)) != NONE){

				colisionArray[i] = true;


				//arrumar essa detecao de colisao, fiz rapido, utilizar colisionArray
				if(i == 0 || i == 1){ //top
					noColision = false;
					this->_dy = 0;
					this->_y ++;
				}else if(i == 2 || i == 3){ //bot
					checkAirborne = true;
					noColision = false;
					this->_dy = 0;
					this->_y --;
				}
				if(i == 0 || i == 2){ //left
					noColision = false;
					this->_dx = 0;
					this->_x ++;
				}else if(i == 1 || i == 3){ //right
					noColision = false;
					this->_dx = 0;
					this->_x --;
				}

				//termina aqui
			}

			if(colisionArray[0]){ //top left colision
				noColision = false;
			}
			if(colisionArray[1]){ //top right colision
				noColision = false;
			}
			if(colisionArray[2]){ //bot left colision
				noColision = false;
			}
			if(colisionArray[3]){ //bot right colision
				noColision = false;
			}
		}

		if(!noColision){
			framesInColision++;
		}else{
			framesInColision = 0;
			if(checkAirborne){
				this->_isAirborne = false;
			}
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
