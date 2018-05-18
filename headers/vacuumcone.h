/*
 * vacuumcone.h
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */


#include "animatedsprite.h"

class VacuumCone: public AnimatedSprite{
public:

	VacuumCone(Graphics &graphics);

	void update(float elapsedTime);

	void animationDone(std::string currentAnimation);

	void setupAnimations();

private:

	Direction _facing;

};

