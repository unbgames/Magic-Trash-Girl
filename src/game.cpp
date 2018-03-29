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


Game::Game(){
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game(){

}

void Game::gameLoop(){
	Graphics graphics;

	SDL_Event event;


	while(true){

		if(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				return;
			}
		}
		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics){
	graphics.clear();

	graphics.flip();
}
