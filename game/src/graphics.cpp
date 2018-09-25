/*
 * graphics.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "globals.h"

Graphics::Graphics(Game &game):
	windowWidth(0),
	windowHeight(0),
	_gameAssociated(&game),
	_fullscreenState(false){
	this->camera = Camera(*this);
	SDL_CreateWindowAndRenderer(globals::INITIAL_SCREEN_WIDTH, globals::INITIAL_SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, globals::WINDOW_NAME.c_str());
}

Graphics::~Graphics(){
	SDL_DestroyWindow(this->_window);
}

/*
 *  \brief retorna a surface do spritesheet q se encontra no filepath dado
 *
 *  	somente a surface � guardada, fica a cargo da classe sprite criar as textures
 */
SDL_Surface* Graphics::loadImage(const std::string &filePath){
	if(this->_spriteSheetsSurfaces.count(filePath) == 0){
		this->_spriteSheetsSurfaces[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheetsSurfaces[filePath];
}

SDL_Texture* Graphics::loadTexture(const std::string &filePath){
	if(this->_spriteSheetsTextures.count(filePath) == 0){
		this->_spriteSheetsTextures[filePath] = SDL_CreateTextureFromSurface(this->getRenderer(), this->loadImage(filePath));
	}
	return this->_spriteSheetsTextures[filePath];
}

/*
 *  \brief chama SDL_RenderCopyEx com o unico render do jogo, os ultimos 3 parametros s�o opcionais, caso n�o dados a fun��o comporta-se como SDL_RenderCopy
 */
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle, SDL_Point* center, SDL_RendererFlip flip){

	SDL_Rect aux = *destinationRectangle;

	aux.x -= this->camera.getx();
	aux.y -= this->camera.gety();

	SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, &aux, angle, center, flip);
}

/*
 *  \brief chama RenderPresent mostrando na tela o que est� presente em renderer
 */
void Graphics::flip(){
	SDL_RenderPresent(this->_renderer);
}

/*
 *  \brief chama RenderClear
 */
void Graphics::clear(){
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const{
	return this->_renderer;
}

void Graphics::updateDisplayInfo(){

	int auxDisplayIndex = SDL_GetWindowDisplayIndex(this->_window);
	if(auxDisplayIndex < 0){
		std::cout << "error em Graphics::updateDisplayInfo :: error message : " << SDL_GetError() << std::endl;
	}else{
		SDL_GetCurrentDisplayMode(auxDisplayIndex, &this->displayInfo);
	}

	SDL_GetWindowSize(this->_window, &this->windowWidth, &this->windowHeight);
}

void Graphics::toggleFullscreen(){
	std::cout << "deu toggle em fullscreen" << std::endl;
	if(this->_fullscreenState){
		SDL_SetWindowFullscreen(this->_window, 0);
		this->_fullscreenState = false;
	}else{
		SDL_SetWindowFullscreen(this->_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		this->_fullscreenState = true;
	}
}

Game* Graphics::getGameAssociated(){
	return this->_gameAssociated;
}

