/*
 * portal.h
 *
 *  Created on: May 26, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_PORTAL_H_
#define SOURCE_HEADERS_PORTAL_H_

#include "animatedsprite.h"

class Portal: public AnimatedSprite{
public:

	Portal(Graphics &graphics, float posX, float posY);
	~Portal();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

private:



};



#endif /* SOURCE_HEADERS_PORTAL_H_ */
