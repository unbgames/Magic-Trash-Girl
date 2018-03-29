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

#include "sprite.h"

namespace {
	const int FPS = 33;
	const int MAX_FRAME_TIME = 1000/FPS;
}

Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
	Graphics graphics;

	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	while(true){

		if(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				return;
			}
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

	graphics.flip();
}

void Game::update(float elapsedtime){

}
