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
#include "backgroundsectorlibraryhandler.h"
#include <ctime>
#include "portal.h"

namespace {
	const int MINFPS = 33;
	const int MAX_FRAME_TIME = 1000/MINFPS;
	const int MAXFPS = 60;
	const int MIN_FRAME_TIME = 1000/MAXFPS;
}

Game* Game::_instance = nullptr;

Game::Game():
	_input(),
	_numberBlocksLine(background_blocks_constants::INITIAL_NUMBER_BLOCKS_LINE),
	_numberBlocksColumn(background_blocks_constants::INITIAL_NUMBER_BLOCKS_COLUMN),
	_quitFlag(false),
	_backgroundSectorHandler(),
	_graphicsAssociated(nullptr){
	_instance = this;
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(time(NULL));
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

	Graphics graphics = Graphics(*this);

	this->_graphicsAssociated = &graphics;

	this->setupBackgroundBlocks(graphics, this->_numberBlocksLine , this->_numberBlocksColumn);

	SDL_Event event;

	int LAST_UPDATE_TIME = SDL_GetTicks();

	this->_player = Player(graphics, player_constants::PLAYER_START_X, player_constants::PLAYER_START_Y);

	this->createNewPseudoRandomBlocksVector(background_blocks_constants::NUMBER_SECTORS_LINE, background_blocks_constants::NUMBER_SECTORS_COLUMN);

	while(true){

		//std::cout << " ======= new frame on game loop ======== " << std::endl;

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
			this->createNewPseudoRandomBlocksVector(background_blocks_constants::NUMBER_SECTORS_LINE, background_blocks_constants::NUMBER_SECTORS_COLUMN);
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
		std::cout << " fps-> " << 1000/ELAPSED_TIME_MS << std::endl;
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

void Game::setupBackgroundBlocks(Graphics &graphics, int lines, int columns){

	this->_numberBlocksLine = lines;
	this->_numberBlocksColumn = columns;

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

void Game::createNewPseudoRandomBlocksVector(int sectorsByLine, int sectorsByColumn){

	this->_player.setPosition(-1100, -1100);

	int auxX = (sectorsByLine*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + 2;
	int auxY = (sectorsByColumn*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS) + 2;

	this->setupBackgroundBlocks(*this->_graphicsAssociated, auxX, auxY);

	for(int j = 0; j < auxY; j++){
		for(int i = 0; i < auxX; i++){
			if((i == 0) || (j==0) || (i == auxX-1) || (j == auxY-1)){
				this->setBlockType(i,j,UNBREAKABLE);
			}
		}
	}

	for(int i = 0; i < sectorsByLine; i++){
		for(int j = 0; j < sectorsByColumn; j++){

			std::vector<BlockType> auxsector = this->_backgroundSectorHandler.getRandomFillerSector().sectorInfo;

			for(int ix = 0; ix < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; ix++){
				for(int jx = 0; jx < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; jx++){
					this->setBlockType(1 + (i*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix , 1 + (j*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS) + jx, auxsector[(jx*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix]);
				}
			}
		}
	}

	/*
	 * 	inicio da criação do caminho obrigatorio; falta setar as flags conforme vai criando
	 */

	std::vector<Vector2> sectorWay;
	std::vector<unsigned int> sectorWayFlags;
	bool wayFound = false;
	Direction lastMove = DOWN;

	sectorWay.push_back(Vector2(rand() % sectorsByLine, 0));

	int aux;

	while(!wayFound){
		switch(lastMove){ //arrumar flags aqui
			case DOWN:

				aux = rand() % 3;

				if(aux == 2){ //left
					if(sectorWay.back().x == 0){
						sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
						sectorWayFlags.push_back(W_TOP_BOT);
					}else{
						sectorWay.push_back(Vector2(sectorWay.back().x - 1,sectorWay.back().y));
						sectorWayFlags.push_back(W_TOP_LEFT);
						lastMove = LEFT;
					}
				}else if(aux == 1){ //right
					if(sectorWay.back().x == (sectorsByLine - 1)){
						sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
						sectorWayFlags.push_back(W_TOP_BOT);
					}else{
						sectorWay.push_back(Vector2(sectorWay.back().x + 1,sectorWay.back().y));
						sectorWayFlags.push_back(W_TOP_RIGHT);
						lastMove = RIGHT;
					}
				}else{ //down
					sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
					sectorWayFlags.push_back(W_TOP_BOT);
				}

			break;
			case LEFT:

				aux = rand() % 2;

				if(aux == 1){ //left
					if(sectorWay.back().x == 0){
						sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
						sectorWayFlags.push_back(W_RIGHT_BOT);
						lastMove = DOWN;
					}else{
						sectorWay.push_back(Vector2(sectorWay.back().x - 1,sectorWay.back().y));
						sectorWayFlags.push_back(W_RIGHT_LEFT);
					}
				}else{ //down
					sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
					sectorWayFlags.push_back(W_RIGHT_BOT);
					lastMove = DOWN;
				}

			break;
			case RIGHT:

				aux = rand() % 2;

				if(aux == 1){ //right
					if(sectorWay.back().x == (sectorsByLine - 1)){
						sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
						sectorWayFlags.push_back(W_LEFT_BOT);
						lastMove = DOWN;
					}else{
						sectorWay.push_back(Vector2(sectorWay.back().x + 1,sectorWay.back().y));
						sectorWayFlags.push_back(W_LEFT_RIGHT);
					}
				}else{ //down
					sectorWay.push_back(Vector2(sectorWay.back().x,sectorWay.back().y + 1));
					sectorWayFlags.push_back(W_LEFT_BOT);
					lastMove = DOWN;
				}


			break;
			case UP:
				std::cout << "error: createNewPseudoRandomBlocksVector criou caminho impossivel" << std::endl;
				wayFound = true;
				this->requestQuit();
			break;
		}

		if(sectorWay.back().y == sectorsByColumn){
			wayFound = true;
			sectorWay.pop_back();
		}
	}

	for(int i = 0; i < (int)sectorWay.size(); i++){
		if(i == 0){
			BlockSector auxsector = this->_backgroundSectorHandler.getRandomStartSector(sectorWayFlags[i]);

			for(int ix = 0; ix < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; ix++){
				for(int jx = 0; jx < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; jx++){
					this->setBlockType(1 + (sectorWay[i].x*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix , 1 + (sectorWay[i].y*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS) + jx, auxsector.sectorInfo[(jx*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix]);
				}
			}

			this->_player.setPosition((1 + (sectorWay[i].x*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS))*64 + auxsector.start_finishPos.x, (1 + (sectorWay[i].y*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS))*64 + auxsector.start_finishPos.y);

		}else if(i == (int)sectorWay.size() - 1){
			BlockSector auxsector = this->_backgroundSectorHandler.getRandomFinishSector(sectorWayFlags[i]);

			for(int ix = 0; ix < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; ix++){
				for(int jx = 0; jx < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; jx++){
					this->setBlockType(1 + (sectorWay[i].x*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix , 1 + (sectorWay[i].y*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS) + jx, auxsector.sectorInfo[(jx*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix]);
				}
			}

			this->addNewSpriteToDraw( new Portal(*this->_graphicsAssociated, (1 + (sectorWay[i].x*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS))*64 + auxsector.start_finishPos.x, (1 + (sectorWay[i].y*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS))*64 + auxsector.start_finishPos.y) );

		}else{

			std::vector<BlockType> auxSectorInfo = this->_backgroundSectorHandler.getRandomFillerSector(sectorWayFlags[i]).sectorInfo;

			for(int ix = 0; ix < background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS; ix++){
				for(int jx = 0; jx < background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS; jx++){
					this->setBlockType(1 + (sectorWay[i].x*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix , 1 + (sectorWay[i].y*background_blocks_constants::NUMBER_BLOCKS_COLUMN_SECTORS) + jx, auxSectorInfo[(jx*background_blocks_constants::NUMBER_BLOCKS_LINE_SECTORS) + ix]);
				}
			}
		}
	}

	/*
	 * 	termino da criação do caminho obrigatorio;
	 */
}

void Game::damageBlock(int indexX, int indexY, float damage){

	if((indexX >= 0 && indexX < this->_numberBlocksLine) && (indexY >= 0 && indexY < this->_numberBlocksColumn)){
		if((this->_backgroundBlocks[indexX + (indexY*this->_numberBlocksLine)].getType() == BREAKABLE)|| (this->_backgroundBlocks[indexX + (indexY*this->_numberBlocksLine)].getType() == BUBLE)){
			this->_backgroundBlocks[indexX + (indexY*this->_numberBlocksLine)].takeDamage(damage);
		}
	}
}

BlockType Game::getBlockType(int indexX, int indexY){
	if((indexX >= 0 && indexX < this->_numberBlocksLine) && (indexY >= 0 && indexY < this->_numberBlocksColumn)){
		return this->_backgroundBlocks[indexX + (indexY*this->_numberBlocksLine)].getType();
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

	if((indexX >= 0 && indexX < this->_numberBlocksLine) && (indexY >= 0 && indexY < this->_numberBlocksColumn)){
		this->_backgroundBlocks[indexX + (indexY*this->_numberBlocksLine)].setType(type);
	}
}

void Game::requestQuit(){
	this->_quitFlag = true;
}

int Game::getCurrentNumberBlocksLine(){
	return this->_numberBlocksLine;
}

int Game::getCurrentNumberBlocksColumn(){
	return this->_numberBlocksColumn;
}
