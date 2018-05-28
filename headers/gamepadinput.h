/*
 * gamepadinput.h
 *
 *  Created on: May 28, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GAMEPADINPUT_H_
#define SOURCE_HEADERS_GAMEPADINPUT_H_

#include "globals.h"

class GamepadInput {
public:

	GamepadInput();
	~GamepadInput();
	void initGamepad();

	void beginNewFrame();

private:

	SDL_GameController* _gamePad;

};



#endif /* SOURCE_HEADERS_GAMEPADINPUT_H_ */
