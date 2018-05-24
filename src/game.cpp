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
	_input(),
	_quitFlag(false),
	_backgroundSectorHandler(),
	_graphicsAssociated(nullptr){
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

	this->_graphicsAssociated = &graphics;

	this->setupBackgroundBlocks(graphics, background_blocks_constants::NUMBER_BLOCKS_COLUMN, background_blocks_constants::NUMBER_BLOCKS_LINE);

	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	this->_player = Player(graphics, player_constants::PLAYER_START_X, player_constants::PLAYER_START_Y);

	this->createNewPseudoRandomBlocksVector();

	while(true){

	//	std::cout << " ======= new frame on game loop ======== " << std::endl;

		graphics.updateDisplayInfo();

		if(this->_quitFlag){
			return;
		}

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

		if(this->_input.isKeyHeld(SDL_SCANCODE_SPACE)){
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

		if(this->_input.wasKeyPressed(SDL_SCANCODE_R)){
			this->createNewPseudoRandomBlocksVector();
		}

		if(this->_input.wasKeyPressed(SDL_SCANCODE_F)){
			graphics.toggleFullscreen();
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

void Game::setupBackgroundBlocks(Graphics &graphics, int columns, int lines){

	this->_backgroundBlocks.clear();

	for(int j = 0; j < columns; j++){
		for(int i = 0; i < lines; i++){
			//std::cout << i << " <- i ::" << j << " <- j " << std::endl;

			SDL_Event PingStop;
			while (SDL_PollEvent(&PingStop)) {}

			this->_backgroundBlocks.reserve(columns * lines);

			this->_backgroundBlocks.push_back(BackgroundBlock(graphics, i, j, NONE));
		}
	}

}

void Game::redoBackgroundBlocksVector(){

	for(int j = 0; j < background_blocks_constants::NUMBER_BLOCKS_COLUMN; j++){
		for(int i = 0; i < background_blocks_constants::NUMBER_BLOCKS_LINE; i++){
			if((i == 0) || (j==0) || (i == background_blocks_constants::NUMBER_BLOCKS_LINE-1) || (j == background_blocks_constants::NUMBER_BLOCKS_COLUMN-1)){
				this->setBlockType(i,j,UNBREAKABLE);
			}else if((i+j)%2 == 0){
				this->setBlockType(i,j,BREAKABLE);
			}else{
				this->setBlockType(i,j,NONE);
			}
		}
	}
}

void Game::createNewPseudoRandomBlocksVector(){

	this->setupBackgroundBlocks(*this->_graphicsAssociated, 34, 34);

	for(int j = 0; j < 34; j++){
		for(int i = 0; i < 34; i++){
			if((i == 0) || (j==0) || (i == 34-1) || (j == 34-1)){
				this->setBlockType(i,j,UNBREAKABLE);
			}
		}
	}

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){

			std::vector<BlockType> auxsector = this->_backgroundSectorHandler.getRandomSector();

			for(int ix = 0; ix < 8; ix++){
				for(int jx = 0; jx < 8; jx++){
					this->setBlockType(1 + (i*8) + ix, 1 + (j*8) + jx,auxsector[(jx*8) + ix]);
				}
			}
		}
	}
}

void Game::damageBlock(int indexX, int indexY, float damage){

	if((indexX >= 0 && indexX < background_blocks_constants::NUMBER_BLOCKS_LINE) && (indexY >= 0 && indexY < background_blocks_constants::NUMBER_BLOCKS_COLUMN)){
		if((this->_backgroundBlocks[indexX + (indexY*background_blocks_constants::NUMBER_BLOCKS_LINE)].getType() == BREAKABLE)|| (this->_backgroundBlocks[indexX + (indexY*background_blocks_constants::NUMBER_BLOCKS_LINE)].getType() == BUBLE)){
			this->_backgroundBlocks[indexX + (indexY*background_blocks_constants::NUMBER_BLOCKS_LINE)].takeDamage(damage);
		}
	}
}

BlockType Game::getBlockType(int indexX, int indexY){
	if((indexX >= 0 && indexX < background_blocks_constants::NUMBER_BLOCKS_LINE) && (indexY >= 0 && indexY < background_blocks_constants::NUMBER_BLOCKS_COLUMN)){
		return this->_backgroundBlocks[indexX + (indexY*background_blocks_constants::NUMBER_BLOCKS_LINE)].getType();
	}else{
		return NONE;
	}
}

void Game::setBlockType(int indexX, int indexY, BlockType type){

	Vector2 auxColision[4];

	float auxX, auxY, auxW, auxH;

	this->_player.getPosSize(&auxX, &auxY, &auxW, &auxH);

	/*
	 * 0 = top left
	 * 1 = top right
	 * 2 = bot left
	 * 3 = bot right
	 */

	auxColision[0] = Vector2((int)(((auxX + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((auxY + 1)/background_blocks_constants::BLOCK_HEIGTH));
	auxColision[1] = Vector2((int)(((auxX + auxW - 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((auxY + 1)/background_blocks_constants::BLOCK_HEIGTH));
	auxColision[2] = Vector2((int)(((auxX + 1)/background_blocks_constants::BLOCK_WIDTH)), (int)((auxY + auxH - 1)/background_blocks_constants::BLOCK_HEIGTH));
	auxColision[3] = Vector2((int)((auxX + auxW - 1)/background_blocks_constants::BLOCK_WIDTH), (int)((auxY + auxH - 1)/background_blocks_constants::BLOCK_HEIGTH));

	for(int i = 0; i < 4; i++){
		if(auxColision[i].x == indexX && auxColision[i].y == indexY){
			std::cout << "tentativa de modificar o bloco onde o player esta" << std::endl;
			return;
		}
	}

	if((indexX >= 0 && indexX < background_blocks_constants::NUMBER_BLOCKS_LINE) && (indexY >= 0 && indexY < background_blocks_constants::NUMBER_BLOCKS_COLUMN)){
		this->_backgroundBlocks[indexX + (indexY*background_blocks_constants::NUMBER_BLOCKS_LINE)].setType(type);
	}
}

void Game::requestQuit(){
	this->_quitFlag = true;
}
