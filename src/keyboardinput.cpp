/*
 * KeyboardInput.cpp
 *
 *  Created on: Apr 16, 2018
 *      Author: TMK
 */

#include <keyboardinput.h>

/*
 *  \brief limpa as flags de keys para o novo frame, pressedKeys se mantem pois uma tecla pode estar pressionada por mais de um frame
 */
void KeyboardInput::beginNewFrame(){
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}

void KeyboardInput::menuTransition(){
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
	this->_heldKeys.clear();
}


void KeyboardInput::keyDownEvent(const SDL_Event& event){
	this->_pressedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = true;
}

void KeyboardInput::keyUpEvent(const SDL_Event& event){
	this->_releasedKeys[event.key.keysym.scancode] = true;
	this->_heldKeys[event.key.keysym.scancode] = false;
}

bool KeyboardInput::wasKeyPressed(SDL_Scancode key){
	return this->_pressedKeys[key];
}

bool KeyboardInput::wasKeyReleased(SDL_Scancode key){
	return this->_releasedKeys[key];
}

bool KeyboardInput::isKeyHeld(SDL_Scancode key){
	return this->_heldKeys[key];
}
