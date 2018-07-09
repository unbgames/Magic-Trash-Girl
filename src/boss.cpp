/*
 * Boss.cpp
 *
 *  Created on: 09/07/2018
 *      Author: gabriel
 */
#include "boss.h"

Boss::Boss(Graphics &graphics, float posX, float posY):
				Enemy(graphics, "assets/boss.png", enemy_constants::BOSS_WIDTH, enemy_constants::BOSS_HEIGHT, posX, posY, 300, enemy_constants::BOSS_HP),
				//_stuckInBubble(false),
				//_storedDxBubble(0),
				//_storedDyBubble(0),
				//_bubbleTimer(0),
				_storedDxColision(0),
				_storedDyColision(0),
				_takingDamageFromPlayerVaccum(false),
				_isAirborne(false),
				_facing(LEFT)
				{
				this->setupAnimations();
				this->playAnimation("IDLE");
}

Boss::~Boss(){

}

void Boss::update(float elapsedTime){
		// todo
}

std::string Boss::getEnemyType(){
	return "Boss";
}


void Boss::resolveColision(std::string objectType){

	if(objectType == "PlayerProjectile"){		// ????
		//this->encaseInBubble();
		_hp--; //?
	}else if(objectType == "VacuumCone"){
		//if(this->_stuckInBubble){
		this->_takingDamageFromPlayerVaccum = true;		///????
		}
	}

void Boss::setupAnimations(){
	this->addAnimation(2, 0, 0, "IDLE", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(2, 0, 0, "MovingRight", this->_w, this->_h, Vector2(0,0));
	this->addAnimation(2, 0, 0, "MovingLeft", this->_w, this->_h, Vector2(0,0), ExVariables(0, nullptr, SDL_FLIP_HORIZONTAL));
}
