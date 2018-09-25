/*
 * sectorbackground.h
 *
 *  Created on: Jun 8, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_SECTORBACKGROUND_H_
#define SOURCE_HEADERS_SECTORBACKGROUND_H_

#include "animatedsprite.h"
#include "globals.h"

class SectorBackground: public AnimatedSprite{
public:

	SectorBackground();

	SectorBackground(Graphics &graphics, std::string filepath, float posX, float posY);

	~SectorBackground();

	void setupAnimations();

	std::string getObjectType();

private:

};



#endif /* SOURCE_HEADERS_SECTORBACKGROUND_H_ */
