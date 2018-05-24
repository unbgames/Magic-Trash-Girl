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

Graphics::Graphics():
	camera(){

	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGTH, 0, &this->_window, &this->_renderer);
	SDL_SetWindowTitle(this->_window, globals::WINDOW_NAME.c_str());
}

Graphics::~Graphics(){
	SDL_DestroyWindow(this->_window);
}

/*
 *  \brief retorna a surface do spritesheet q se encontra no filepath dado
 *
 *  	somente a surface é guardada, fica a cargo da classe sprite criar as textures
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
 *  \brief chama SDL_RenderCopyEx com o unico render do jogo, os ultimos 3 parametros são opcionais, caso não dados a função comporta-se como SDL_RenderCopy
 */
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle, SDL_Point* center, SDL_RendererFlip flip){

	SDL_Rect aux = *destinationRectangle;

	aux.x -= this->camera.getx() - (globals::SCREEN_WIDTH)/2;
	aux.y -= this->camera.gety()	 - (globals::SCREEN_HEIGTH)/2;

	SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, &aux, angle, center, flip);
}

/*
 *  \brief chama RenderPresent mostrando na tela o que está presente em renderer
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
