/*
 * game.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include <iostream>


#include "animatedsprite.h"

namespace {
	const int FPS = 33;
	const int MAX_FRAME_TIME = 1000/FPS;
}

Game::Game():
	_input(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){

	Graphics graphics;

	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	this->_player = Player(graphics, 100, 100);

	while(true){

		this->_input.beginNewFrame();

		if(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				if(event.key.repeat == 0){
					this->_input.keyDownEvent(event);
				}
			}
			else if(event.type == SDL_KEYUP){
				this->_input.keyUpEvent(event);
			}
			if(event.type == SDL_QUIT){
				return;
			}
		}

		if(this->_input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
			return;
		}

		if(this->_input.isKeyHeld(SDL_SCANCODE_LEFT)){
			this->_player.moveLeft();
		}
		else if(this->_input.isKeyHeld(SDL_SCANCODE_RIGHT)){
			this->_player.moveRight();
		}
		if(!this->_input.isKeyHeld(SDL_SCANCODE_LEFT) && !this->_input.isKeyHeld(SDL_SCANCODE_RIGHT)){
			this->_player.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics){
	graphics.clear();

	  for (std::vector<AnimatedSprite>::iterator it = this->spritesToDraw.begin() ; it != this->spritesToDraw.end(); ++it){
//		 it->draw(graphics, 100, 100);
	  }

		this->_player.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedtime){

	  for (std::vector<AnimatedSprite>::iterator it = this->spritesToDraw.begin() ; it != this->spritesToDraw.end(); ++it){
//		 it->update(elapsedtime);
	  }

	  this->_player.update(elapsedtime);

}
