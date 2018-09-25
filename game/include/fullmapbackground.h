/*
 * fullmapbackground.h
 *
 *  Created on: Jul 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_FULLMAPBACKGROUND_H_
#define SOURCE_HEADERS_FULLMAPBACKGROUND_H_

#include "animatedsprite.h"
#include "globals.h"

class FullMapBackground: public AnimatedSprite{
public:

	FullMapBackground();

	FullMapBackground(Graphics &graphics, std::string filepath, int width, int height, float posX, float posY);

	~FullMapBackground();

	void setupAnimations();

	std::string getObjectType();

private:

};




#endif /* SOURCE_HEADERS_FULLMAPBACKGROUND_H_ */
