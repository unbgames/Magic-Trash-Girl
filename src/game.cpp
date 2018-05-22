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
	const int MINFPS = 33;
	const int MAX_FRAME_TIME = 1000/MINFPS;
	const int MAXFPS = 60;
	const int MIN_FRAME_TIME = 1000/MAXFPS;
}

Game* Game::_instance = nullptr;

Game::Game():
	_input(){
	_instance = this;
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game(){
	this->_spritesToDraw.clear();
}

Game& Game::getInstance(){
	if(_instance == nullptr){
		_instance = new Game();
	}
	return *_instance;
}


void Game::gameLoop(){

	Graphics graphics = Graphics();

	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	this->_player = Player(graphics, player_constants::PLAYER_START_X, player_constants::PLAYER_START_Y);

	this->setupBackgroundBlocks(graphics);

	while(true){

		this->_input.beginNewFrame();

		while(SDL_PollEvent(&event)){
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
		}else if(this->_input.isKeyHeld(SDL_SCANCODE_RIGHT)){
			this->_player.moveRight();
		}else if(this->_input.isKeyHeld(SDL_SCANCODE_UP) && !this->_input.isKeyHeld(SDL_SCANCODE_DOWN)){
			this->_player.lookUp();
		}else if(this->_input.isKeyHeld(SDL_SCANCODE_DOWN) && !this->_input.isKeyHeld(SDL_SCANCODE_UP)){
			this->_player.lookDown();
		}else{
			this->_player.stopMoving();
		}

		if(this->_input.wasKeyPressed(SDL_SCANCODE_SPACE)){
			this->_player.jump();
		}

		if(this->_input.wasKeyPressed(SDL_SCANCODE_Z)){
			this->_player.bubble();
		}

		if(this->_input.wasKeyPressed(SDL_SCANCODE_X)){
			this->_player.startVacuum();
		}

		if(this->_input.wasKeyReleased(SDL_SCANCODE_X)){
			this->_player.stopVacuum();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		if(ELAPSED_TIME_MS < MIN_FRAME_TIME){
			SDL_Delay(MIN_FRAME_TIME - ELAPSED_TIME_MS);
			const int CURRENT_TIME_MS = SDL_GetTicks();
			ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		}
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	}
}

void Game::draw(Graphics &graphics){
	graphics.clear();

	for (std::vector<BackgroundBlock>::iterator it = this->_backgroundBlocks.begin() ; it != this->_backgroundBlocks.end(); ++it){
		 it->draw(graphics);
	}

	for (std::vector<std::unique_ptr<AnimatedSprite>>::iterator it = this->_spritesToDraw.begin() ; it != this->_spritesToDraw.end(); ++it){
		 (*it)->draw(graphics);
	}

	this->_player.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedtime){

	for (std::vector<BackgroundBlock>::iterator it = this->_backgroundBlocks.begin() ; it != this->_backgroundBlocks.end(); ++it){
		 it->update(elapsedtime);
	}

	for(unsigned int i = 0; i < this->_spritesToDraw.size(); i++){

		this->_spritesToDraw[i]->update(elapsedtime);

		if(this->_spritesToDraw[i]->getToBeDeleted()){
			std::vector<std::unique_ptr<AnimatedSprite>>::iterator it = this->_spritesToDraw.begin();
			this->_spritesToDraw.erase(it + i);
		}
	}

	this->_player.update(elapsedtime);

}

void Game::addNewSpriteToDraw(AnimatedSprite* sprite){

	std::unique_ptr<AnimatedSprite> auxPtr(sprite);

	this->_spritesToDraw.push_back(std::move(auxPtr));

}

void Game::setupBackgroundBlocks(Graphics &graphics){

	for(int j = 0; j < 9; j++){
		for(int i = 0; i < 16; i++){
			if((i == 0) || (j==0) || (i == 15) || (j == 8)){
				this->_backgroundBlocks.push_back(BackgroundBlock(graphics, i, j, UNBREAKABLE));
			}else if((i+j)%2 == 0){
				this->_backgroundBlocks.push_back(BackgroundBlock(graphics, i, j, BREAKABLE));
			}else{
				this->_backgroundBlocks.push_back(BackgroundBlock(graphics, i, j, NONE));
			}
		}
	}
}

void Game::damageBlock(int indexX, int indexY, float damage){
	if((indexX >= 0 && indexX < background_blocks_constants::NUMBER_BLOCKS_LINE) && (indexY >= 0 && indexY < background_blocks_constants::NUMBER_BLOCKS_COLUMN)){
		if(this->_backgroundBlocks[indexX + (indexY*16)].getType() == BREAKABLE){
			this->_backgroundBlocks[indexX + (indexY*16)].takeDamage(damage);
		}
	}
}
