/*
 * rat.h
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_RAT_H_
#define SOURCE_HEADERS_RAT_H_

#include "enemy.h"

class Rat:public Enemy{
public:

	Rat(Graphics &graphics, float posX, float posY);

	~Rat();

	void update(float elpasedTime);

	std::string getEnemyType();

	void resolveColision(std::string objectType);

	void setupAnimations();

	void encaseInBubble();

	void freeFromBubble();


private:

	bool _stuckInBubble;
	float _storedDxBubble;
	float _storedDyBubble;

	float _bubbleTimer;

	float _storedDxColision;
	float _storedDyColision;

	bool _takingDamageFromPlayerVaccum;

	bool _isAirborne;

	Direction _facing;
};

#endif /* SOURCE_HEADERS_RAT_H_ */
