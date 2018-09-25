/*
 * playerprojetil.h
 *
 *  Created on: May 17, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_PLAYERPROJECTILE_H_
#define SOURCE_HEADERS_PLAYERPROJECTILE_H_

#include "animatedsprite.h"

class PlayerProjectile: public AnimatedSprite{
public:
	PlayerProjectile(Graphics &graphics, float posX, float posY, Direction facing);

	void update(float elapsedTime);

	void animationDone(std::string currentAnimation);

	void setupAnimations();

	std::string getObjectType();

	void resolveColision(std::string objectType);

private:

	Direction _facing;

	float _lifeTime;

};



#endif /* SOURCE_HEADERS_PLAYERPROJECTILE_H_ */
