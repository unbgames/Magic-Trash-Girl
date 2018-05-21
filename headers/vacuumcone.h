/*
 * vacuumcone.h
 *
 *  Created on: May 18, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_VACUUMCONE_H_
#define SOURCE_HEADERS_VACUUMCONE_H_

#include "animatedsprite.h"

class VacuumCone: public AnimatedSprite{
public:

	VacuumCone();

	VacuumCone(Graphics &graphics);

	void update(float elapsedTime);

	void animationDone(std::string currentAnimation);

	void setupAnimations();

private:

	Direction _facing;

	float _dps;

};


#endif /* SOURCE_HEADERS_VACUUMCONE_H_ */
