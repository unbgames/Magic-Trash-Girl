/*
 * gamepadinput.h
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GAMEPADINPUT_H_
#define SOURCE_HEADERS_GAMEPADINPUT_H_

#include "globals.h"
#include <map>

class GamepadInput {
public:

	GamepadInput();
	~GamepadInput();
	void initGamepad();
	void closeGamepad();

	void beginNewFrame();
	void menuTransition();
	void buttonUpEvent(const SDL_Event& event);
	void buttonDownEvent(const SDL_Event& event);

	bool wasbuttonPressed(Uint8 button);
	bool wasbuttonReleased(Uint8 button);
	bool isbuttonHeld(Uint8 button);


private:

	SDL_GameController* _gamepad;
	SDL_JoystickID _gamepadId;

	std::map<Uint8, bool> _heldButtons;
	std::map<Uint8, bool> _pressedButtons;
	std::map<Uint8, bool> _releasedButtons;

};



#endif /* SOURCE_HEADERS_GAMEPADINPUT_H_ */
