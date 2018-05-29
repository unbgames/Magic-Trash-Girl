/*
 * pausemenu.h
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_PAUSEMENU_H_
#define SOURCE_HEADERS_PAUSEMENU_H_

#include "menu.h"

class PauseMenu:public Menu{
public:

	PauseMenu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput);

	~PauseMenu();

	void update(float elapsedTime);

	void handleEvents();

	std::string getMenuType();

	void setupButtons();

private:

	void activateButton();

};

#endif /* SOURCE_HEADERS_PAUSEMENU_H_ */
