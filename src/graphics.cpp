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

Graphics::Graphics(){

	std::cout << "passoua qui";

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
	if(this->_spriteSheets.count(filePath) == 0){
		this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_spriteSheets[filePath];
}

/*
 *  \brief chama SDL_RenderCopyEx com o unico render do jogo, os ultimos 3 parametros são opcionais, caso não dados a função comporta-se como SDL_RenderCopy
 */
void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, double angle, SDL_Point* center, SDL_RendererFlip flip){
	SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, angle, center, flip);
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
