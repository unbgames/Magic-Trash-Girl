/*
 * enemy.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#include "enemy.h"

Enemy::Enemy(){ // @suppress("Class members should be properly initialized")

}

Enemy::Enemy(Graphics &graphics, std::string filePath, int width, int height, float posX, float posY, float timeToUpdate, int hp):
			AnimatedSprite(graphics, filePath, 0, 0, width, height, posX, posY, timeToUpdate),
			_hp(hp)
			{

}

void Enemy::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

std::string Enemy::getObjectType(){
	return "Enemy";
}
