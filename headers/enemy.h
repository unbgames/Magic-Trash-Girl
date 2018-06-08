/*
 * enemy.h
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_ENEMY_H_
#define SOURCE_HEADERS_ENEMY_H_

#include "animatedsprite.h"


class Enemy: public AnimatedSprite{
public:

	Enemy();

	Enemy(Graphics &graphics, std::string filePath, int width, int height, float posX, float posY, float timeToUpdate, int hp);

	virtual void update(float elapsedTime);

	std::string getObjectType();

	virtual std::string getEnemyType() = 0;

protected:

	virtual void setupAnimations() = 0;

	int _hp;

private:

};


#endif /* SOURCE_HEADERS_ENEMY_H_ */
