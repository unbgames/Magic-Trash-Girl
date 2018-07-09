/*
 * boss.h
 *
 *  Created on: 09/07/2018
 *      Author: gabriel
 */

#ifndef HEADERS_BOSS_H_
#define HEADERS_BOSS_H_
#include "enemy.h"

class Boss : public Enemy{
public:
	Boss(Graphics &graphics, float posX, float posY);

	~Boss();

	void update(float elpasedTime);

	std::string getEnemyType();

	void resolveColision(std::string objectType);

	void setupAnimations();

	//void encaseInBubble();

	//void freeFromBubble();


	private:

	//bool _stuckInBubble;
	//float _storedDxBubble;
	//float _storedDyBubble;

	//float _bubbleTimer;

	float _storedDxColision;
	float _storedDyColision;

	bool _takingDamageFromPlayerVaccum;

	bool _isAirborne;

	Direction _facing;
};




#endif /* HEADERS_BOSS_H_ */
