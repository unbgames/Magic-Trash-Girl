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

	MenuButton(std::string name, Graphics &graphics, float offsetX, float offsetY, std::string spritesheetPath, float widthFactor, float heightFactor, Menu& menuAssociated);
	~MenuButton();

	void update(float elapsedTime);

	void setupAnimations();

	std::string getObjectType();

	std::string getName();

	void setupIdleAnimation(int frames, int x, int y, int width, int height, Vector2 offset, ExVariables exVariables = ExVariables());

	void setupActiveAnimation(int frames, int x, int y,int width, int height, Vector2 offset, ExVariables exVariables = ExVariables());

private:

	Menu* _menuAssociated;

	std::string _name;

	float _offsetX,_offsetY, _widthFactor, _heightFactor;

};



#endif /* SOURCE_HEADERS_MENUBUTTON_H_ */
