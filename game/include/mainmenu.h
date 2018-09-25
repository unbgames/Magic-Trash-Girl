/*
 * mainmenu.h
 *
 *  Created on: May 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_MAINMENU_H_
#define SOURCE_HEADERS_MAINMENU_H_

#include "menu.h"
#include "Sound.h"

class MainMenu:public Menu{
public:

	MainMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput);
	~MainMenu();

	void update(float elapsedTime);

	void handleEvents();

	std::string getMenuType();

	void setupButtons();

private:

	void activateButton();

	float _camDesX, _camDesY;

	Sound *click;

};

#endif /* SOURCE_HEADERS_MAINMENU_H_ */
