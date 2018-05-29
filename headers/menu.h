/*
 * menu.h
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_MENU_H_
#define SOURCE_HEADERS_MENU_H_

#include "globals.h"
#include "menubackground.h"
#include "gamepadinput.h"
#include "keyboardinput.h"
#include "menubutton.h"

class Menu{
public:

	Menu(Graphics &graphics, KeyboardInput &keyboardInput, GamepadInput &gamepadInput);
	virtual ~Menu();

	virtual void update(float elapsedTime);
	virtual void draw();

	virtual void handleEvents() = 0;

	virtual std::string getMenuType() = 0;

	virtual void setupButtons() = 0;

	bool getRequestPop();

	void getPosSize(float* x, float* y, int* w, int* h);

protected:

	void addButton();

	Graphics* _graphicsAssociated;

	MenuBackground _background;

	KeyboardInput* _keyboardInput;

	GamepadInput* _gamepadInput;

	bool _requestPop;

	std::vector<MenuButton> _buttonsVector;

	float _x,_y;
	int _w,_h;

private:


};



#endif /* SOURCE_HEADERS_MENU_H_ */
