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

	Portal(Graphics &graphics, float posX, float posY, std::string type = "pseudoRandomLevel", std::string local = "none");
	~Portal();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

	void takeContextAction(std::string objectType);

	void animationDone(std::string currentAnimation);

private:

	std::string _type;

	std::string _local;

	void _loadAssociatedLevel();

};



#endif /* SOURCE_HEADERS_PORTAL_H_ */
