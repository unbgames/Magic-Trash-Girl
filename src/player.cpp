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
		AnimatedSprite(graphics, "assets/Sprites_Karen.png", 0, 0, player_constants::PLAYER_WIDTH, player_constants::PLAYER_HEIGTH, posX, posY, 300),
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
	this->addAnimation(5, 0, 0, "IdleRight", 40,64, Vector2 (0,0));
	this->addAnimation(5, 0, 0, "IdleLeft", 40,64, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(5, 0, 0, "MoveRight", 40,64, Vector2 (0,0));
	this->addAnimation(5, 0, 0, "MoveLeft", 40,64, Vector2 (0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
	this->addAnimation(5, 0, 0, "LookUp", 40,64, Vector2 (0,0),ExVariables(270, nullptr, SDL_FLIP_NONE));
	this->addAnimation(5, 0, 0, "LookDown", 40,64, Vector2 (0,0), ExVariables(90, nullptr, SDL_FLIP_NONE));

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

		Vector2 auxCheckBuble[2];

		auxCheckBuble[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
		auxCheckBuble[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

		if(((Game::getInstance().getBlockType(auxCheckBuble[0].x, auxCheckBuble[0].y)) == BUBLE) || ((Game::getInstance().getBlockType(auxCheckBuble[1].x, auxCheckBuble[1].y)) == BUBLE)){
			this->_dy = player_constants::BUBLE_JUMP_SPEED;
		//	std::cout << "BUBLE JUMP" << std::endl;
		}else{
			this->_dy = player_constants::NORMAL_JUMP_SPEED;
		}


	}
}

void Player::lookUp(){
		this->_dx = 0.0f;

		if((this->_facing == LEFT) || (this->_facing == RIGHT)){
			this->_idleFacing = this->_facing;
		}
		this->_facing = UP;
		this->playAnimation("LookUp");
}

void Player::lookDown(){
		this->_dx = 0.0f;

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

	if(this->_startJump){
		this->_isAirborne = true;
		this->_startJump = false;
	}

	if(this->_isAirborne){
		this->_dy += 0.002 * elapsedTime;
	}

	/*
	 * check de estado de airborne
	 */

	Vector2 auxCheckAirborne[2];

	auxCheckAirborne[0] = Vector2((int)(((this->_x + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));
	auxCheckAirborne[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h)/background_blocks_constants::BLOCK_HEIGTH));

	if(((Game::getInstance().getBlockType(auxCheckAirborne[0].x, auxCheckAirborne[0].y)) == NONE) && ((Game::getInstance().getBlockType(auxCheckAirborne[1].x, auxCheckAirborne[1].y)) == NONE)){
		this->_isAirborne = true;
	}

	/*
	 * check de colision
	 */

	int pixelsToCheckVertical = (int)(this->_y + (this->_dy * elapsedTime)) - (int)this->_y ;
	int pixelsToCheckHorizontal = (int)(this->_x + (this->_dx * elapsedTime)) - (int)this->_x ;

	Vector2 auxCheckColision[4];

	float fauxX = 0;
	int auxY = 0;
	int auxX = 0;
	float auxXncI = 0;
	bool foundVerticalColision = false;
	bool foundHorizontalColision = false;
	if(!(pixelsToCheckVertical < 1)){
		auxXncI = (float)pixelsToCheckHorizontal/(float)std::abs(pixelsToCheckVertical);
	}

	if(pixelsToCheckVertical != 0 && pixelsToCheckHorizontal != 0){
		for(int j = 1; j <= std::abs(pixelsToCheckVertical) ;j++){

			fauxX += auxXncI;
			auxY = (pixelsToCheckVertical > 0) ? j : j*-1;
			auxX = (int)fauxX;

			auxCheckColision[0] = Vector2((int)(((this->_x-1 + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y -1 + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[1] = Vector2((int)(((this->_x + this->_w + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y - 1 + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[2] = Vector2((int)(((this->_x-1 + auxX)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h + auxY)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckColision[3] = Vector2((int)((this->_x + this->_w + auxX)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y+ this->_h + auxY)/background_blocks_constants::BLOCK_HEIGTH));

			/*
			 * 0 = top left
			 * 1 = top right
			 * 2 = bot left
			 * 3 = bot right
			 */

			/*
			 * check de colision para a direita com movimento vertical;
			 */

			if((this->_dx > 0) && (((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != NONE))){
				foundHorizontalColision = true;

				fauxX -= auxXncI;
				auxX = (int)fauxX;

				this->_x += auxX;
			}
			if((this->_dx < 0) && (((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != NONE))){
				foundHorizontalColision = true;

				fauxX -= auxXncI;
				auxX = (int)fauxX;

				this->_x += auxX;
			}
			if((this->_dy > 0) && (((Game::getInstance().getBlockType(auxCheckColision[2].x, auxCheckColision[2].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckColision[3].x, auxCheckColision[3].y)) != NONE))){
				foundVerticalColision = true;

				this->_isAirborne = false;
				this->_y += auxY - 1;
			}
			if((this->_dy < 0) && (((Game::getInstance().getBlockType(auxCheckColision[0].x, auxCheckColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckColision[1].x, auxCheckColision[1].y)) != NONE))){
				foundVerticalColision = true;

				this->_y += auxY + 1;
			}
			if(foundHorizontalColision || foundVerticalColision){
				break;
			}
		}

	}

	/*
	 * check de colision para a direita
	 */

	if(pixelsToCheckHorizontal > 0){
			for(int i = 1; i <= pixelsToCheckHorizontal ; i++){

				Vector2 auxCheckRightColision[2];

				auxCheckRightColision[0] = Vector2((int)(((this->_x + this->_w - 1 + i)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
				auxCheckRightColision[1] = Vector2((int)((this->_x + this->_w - 1 + i)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y)/background_blocks_constants::BLOCK_HEIGTH));

				if(((Game::getInstance().getBlockType(auxCheckRightColision[0].x, auxCheckRightColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckRightColision[1].x, auxCheckRightColision[1].y)) != NONE)){
				this->_x += i - 1;
					this->_dx = 0;
					break;

				}
			}
		}

	/*
	 * check de colision para a esquerda
	 */

	if(pixelsToCheckHorizontal < 0){
		for(int i = -1; i >= pixelsToCheckHorizontal ; i--){

			Vector2 auxCheckLeftColision[2];

			auxCheckLeftColision[0] = Vector2((int)(((this->_x + i)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y+ this->_h - 1)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckLeftColision[1] = Vector2((int)((this->_x + i)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y)/background_blocks_constants::BLOCK_HEIGTH));

			if(((Game::getInstance().getBlockType(auxCheckLeftColision[0].x, auxCheckLeftColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckLeftColision[1].x, auxCheckLeftColision[1].y)) != NONE)){
				this->_x += i + 1;
				this->_dx = 0;
				break;
			}
		}
	}

	/*
	 * check de colision para cima
	 */

	if(pixelsToCheckVertical < 0){
		for(int i = -1; i >= pixelsToCheckVertical ; i--){

			Vector2 auxCheckUpColision[2];

			auxCheckUpColision[0] = Vector2((int)(((this->_x)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + i)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckUpColision[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y + i)/background_blocks_constants::BLOCK_HEIGTH));

			if(((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != NONE)){

				this->_y += i + 1;
				this->_dy = 0;
				break;
			}
		}
	}

	/*
	 * check de colision para baixo
	 */

	if(pixelsToCheckVertical > 0){
		for(int i = 1; i <= pixelsToCheckVertical ; i++){

			Vector2 auxCheckUpColision[2];

			auxCheckUpColision[0] = Vector2((int)(((this->_x)/background_blocks_constants::BLOCK_WIDTH)), (int)((this->_y + this->_h + i)/background_blocks_constants::BLOCK_HEIGTH));
			auxCheckUpColision[1] = Vector2((int)((this->_x + this->_w - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((this->_y + this->_h + i)/background_blocks_constants::BLOCK_HEIGTH));

			if(((Game::getInstance().getBlockType(auxCheckUpColision[0].x, auxCheckUpColision[0].y)) != NONE) || ((Game::getInstance().getBlockType(auxCheckUpColision[1].x, auxCheckUpColision[1].y)) != NONE)){

				this->_isAirborne = false;
				this->_y += i;
				this->_dy = 0;
				break;

			}
		}
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	/*
	 * correção caso haja colisão;
	 */

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

			}
			bool correctTop = false;
			bool correctBot = false;
			bool correctRight = false;
			bool correctLeft = false;

			//essas correçoes não sao perfeitas, arrumar depois

			if(colisionArray[0]){ //top left colision
				//std::cout << "0 correction" << std::endl;
				noColision = false;
				correctTop = true;
				correctLeft = true;
			}
			if(colisionArray[1]){ //top right colision
				//std::cout << "1 correction" << std::endl;
				noColision = false;
				correctTop = true;
				correctRight = true;
			}
			if(colisionArray[2]){ //bot left colision
				//std::cout << "2 correction" << std::endl;
				noColision = false;
				correctBot = true;
				correctLeft = true;
			}
			if(colisionArray[3]){ //bot right colision
				//std::cout << "3 correction" << std::endl;
				noColision = false;
				correctBot = true;
				correctRight = true;
			}

			if(correctTop){ //top
				std::cout << "top correction" << std::endl;
				noColision = false;
				this->_y ++;
			}
			if(correctBot){ //bot
				std::cout << "bot correction" << std::endl;
				checkAirborne = true;
				noColision = false;
				this->_y --;
			}
			if(correctLeft){ //left
				std::cout << "left correction" << std::endl;
				noColision = false;
				this->_x ++;
			}
			if(correctRight){ //right
				std::cout << "right correction" << std::endl;
				noColision = false;
				this->_x --;
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

	/*
	 * termino da correção
	 */

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
