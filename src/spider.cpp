/*
 * spider.cpp
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#include "spider.h"
#include "game.h"

Spider::Spider(Graphics &graphics, float posX, float posY):
				Enemy(graphics, "assets/spider.png", enemy_constants::SPYDER_WIDTH, enemy_constants::SPYDER_HEIGHT, posX, posY, 300, enemy_constants::SPIDER_HP),
				_stuckInBubble(false),
				_bubbleTimer(0),
				_takingDamageFromPlayerVaccum(false)
				{
				this->setupAnimations();
				this->playAnimation("IDLE");
}

Spider::~Spider(){

}

void Spider::update(float elapsedTime){

	if(this->_takingDamageFromPlayerVaccum){
		this->_hp -= (elapsedTime/1000) * Game::getInstance().getPlayerVaccumDps();
		this->_takingDamageFromPlayerVaccum = false;
	}

	if(this->_stuckInBubble){
		_bubbleTimer += elapsedTime;
		if(_bubbleTimer > 3000){
			this->freeFromBubble();
		}
	}

	if(this->_hp < 0){
		this->setToBeDeleted(true);
	}

	AnimatedSprite::update(elapsedTime);
}

std::string Spider::getEnemyType(){
	return "Spider";
}

void Spider::resolveColision(std::string objectType){

	if(objectType == "PlayerProjectile"){
		this->encaseInBubble();
	}else if(objectType == "VacuumCone"){
		if(this->_stuckInBubble){
			this->_takingDamageFromPlayerVaccum = true;
		}
	}

}

void Spider::encaseInBubble(){
	this->_stuckInBubble = true;
	this->playAnimation("StuckInBubble");
}

void Spider::freeFromBubble(){
	this->_stuckInBubble = false;
	this->playAnimation("IDLE");
	this->_bubbleTimer = 0;
}

void Spider::setupAnimations(){

	this->addAnimation(1, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(1, 0, this->_h, "StuckInBubble", this->_w, this->_h, Vector2(0,0));

}
