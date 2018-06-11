/*
 * hudelement.h
 *
 *  Created on: Jun 11, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_HUDELEMENT_H_
#define SOURCE_HEADERS_HUDELEMENT_H_

#include "globals.h"
#include "animatedsprite.h"

class HUDElement: public AnimatedSprite{
public:

	HUDElement();

	HUDElement(Graphics &graphics, float posRelX, float posRelY, float fullHDWidth, float fullHDHeight, std::string filePath);
	~HUDElement();

	virtual void update(float elapsedTime);

	virtual std::string getObjectType();

protected:

	virtual void setupAnimations() = 0;

	float _posRelX, _posRelY, _fullHDWidth, _fullHDHeight;

private:

};



#endif /* SOURCE_HEADERS_HUDELEMENT_H_ */
