/*
 * KeyboardInput.h
 *
 *  Created on: Apr 16, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_KEYBOARDINPUT_H_
#define SOURCE_HEADERS_KEYBOARDINPUT_H_

#include <SDL2/SDL.h>
#include <map>

/*
 *  CLass KeyboardInput
 *
 *	Como em gameplay o unico jogador somente tem controle do objeto player somente haverá 1 classe input, sua unica instancia encontra em game e somente poderá ser acessada no game loop
 *
 */

class KeyboardInput {
public:
	void beginNewFrame();
	void menuTransition();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};



#endif /* SOURCE_HEADERS_KEYBOARDINPUT_H_ */
