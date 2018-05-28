/*
 * menubackground.h
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_MENUBACKGROUND_H_
#define SOURCE_HEADERS_MENUBACKGROUND_H_

#include "globals.h"
#include "animatedsprite.h"

class MenuBackground: public AnimatedSprite{
public:

	MenuBackground();

	MenuBackground(Graphics &graphics, int width, int height, std::string filepath);
	~MenuBackground();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

private:

	int _defaultWidth, _defaultHeight;

};


#endif /* SOURCE_HEADERS_MENUBACKGROUND_H_ */
