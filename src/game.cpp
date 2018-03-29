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

	AnimatedSprite test(graphics, "assets/test.png", 0, 0, 64, 32, 100, 100, 100);

	std::string name = "idle";

	test.addAnimation(2,0,0,name,32,32,Vector2 (0,0));

	test.playAnimation("idle");

	this->spritesToDraw.push_back(test);

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

	  for (std::vector<AnimatedSprite>::iterator it = this->spritesToDraw.begin() ; it != this->spritesToDraw.end(); ++it){
		 it->draw(graphics, 100, 100);
	  }


	graphics.flip();
}

void Game::update(float elapsedtime){

	  for (std::vector<AnimatedSprite>::iterator it = this->spritesToDraw.begin() ; it != this->spritesToDraw.end(); ++it){
		 it->update(elapsedtime);
	  }

}
