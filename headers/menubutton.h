/*
 * menubutton.h
 *
 *  Created on: May 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_MENUBUTTON_H_
#define SOURCE_HEADERS_MENUBUTTON_H_

#include "animatedsprite.h"

class Menu;

class MenuButton: public AnimatedSprite{
public:

	MenuButton(Graphics &graphics, float offsetX, float offsetY, std::string spritesheetPath, float widthFactor, float heightFactor, Menu& menuAssociated);
	~MenuButton();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

private:

	Menu* _menuAssociated;

	float _offsetX,_offsetY, _widthFactor, _heightFactor;

};



#endif /* SOURCE_HEADERS_MENUBUTTON_H_ */
