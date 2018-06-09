/*
 * spider.h
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_SPIDER_H_
#define SOURCE_HEADERS_SPIDER_H_

#include "enemy.h"

class Spider:public Enemy{
public:

	Spider(Graphics &graphics, float posX, float posY);

	~Spider();

	void update(float elpasedTime);

	std::string getEnemyType();

	void resolveColision(std::string objectType);

	void setupAnimations();

	void encaseInBubble();

	void freeFromBubble();


private:

	bool _stuckInBubble;
	float _storedDx;
	float _storedDy;

	float _bubbleTimer;

	bool _takingDamageFromPlayerVaccum;

	bool _isAirborne;

	Direction _facing;
};

#endif /* SOURCE_HEADERS_SPIDER_H_ */
