/*
 * spider.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#include "spider.h"

Spider::Spider(Graphics &graphics, float posX, float posY):
				Enemy(graphics, "assets/spider.png", enemy_constants::SPYDER_WIDTH, enemy_constants::SPYDER_HEIGHT, posX, posY, 300, enemy_constants::SPIDER_HP)
				{
				this->setupAnimations();
				this->playAnimation("IDLE");
}

Spider::~Spider(){

}

void Spider::update(float elapsedTime){
	AnimatedSprite::update(elapsedTime);
}

std::string Spider::getEnemyType(){
	return "Spider";
}

void Spider::setupAnimations(){

	this->addAnimation(2, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));

}
