/*
 * playerprojetil.cpp
 *
 *  Created on: May 17, 2018
 *      Author: TMK
 */

#include <playerprojectile.h>
#include <iostream>
#include "game.h"

PlayerProjectile::PlayerProjectile(Graphics &graphics, float posX, float posY, Direction facing):
		AnimatedSprite(graphics, "assets/playerprojetil.png", 0, 0, 24, 24, posX, posY, 1000),
		_facing(facing),
		_lifeTime(0){
	this->setupAnimations();
	this->playAnimation("basic");
}

void PlayerProjectile::update(float elapsedTime){

	this->_lifeTime += elapsedTime;

	if(this->_lifeTime > 5000){
		this->setToBeDeleted(true);
	}

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

	bool noColision = true;


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
		this->setToBeDeleted(true);
		switch(this->_facing){
			case UP:
				if(colisionArray[0]){
					Game::getInstance().setBlockType(auxColision[0].x, auxColision[0].y + 1, BUBLE);
				}else if(colisionArray[1]){
					Game::getInstance().setBlockType(auxColision[1].x, auxColision[1].y + 1, BUBLE);
				}
			break;
			case DOWN:
				if(colisionArray[2]){
					Game::getInstance().setBlockType(auxColision[2].x, auxColision[2].y - 1, BUBLE);
				}else if(colisionArray[3]){
					Game::getInstance().setBlockType(auxColision[3].x, auxColision[3].y - 1, BUBLE);
				}
			break;
			case LEFT:
				if(colisionArray[2]){
					Game::getInstance().setBlockType(auxColision[2].x + 1, auxColision[2].y, BUBLE);
				}else if(colisionArray[0]){
					Game::getInstance().setBlockType(auxColision[0].x + 1, auxColision[0].y, BUBLE);
				}
			break;
			case RIGHT:
				if(colisionArray[1]){
					Game::getInstance().setBlockType(auxColision[1].x - 1, auxColision[1].y, BUBLE);
				}else if(colisionArray[3]){
					Game::getInstance().setBlockType(auxColision[3].x - 1, auxColision[3].y - 1, BUBLE);
				}
			break;
		}
	}

	AnimatedSprite::update(elapsedTime);
}

void PlayerProjectile::animationDone(std::string currentAnimation){

}

void PlayerProjectile::setupAnimations(){
	this->addAnimation(1, 0, 0, "basic", 64,64, Vector2 (0,0));
}

std::string PlayerProjectile::getObjectType(){
	return "PlayerProjectile";
}

void PlayerProjectile::resolveColision(std::string objectType){

	if(objectType == "Enemy"){
		this->setToBeDeleted(true);
	}

}
