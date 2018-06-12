/*
 * textcaches.cpp
 *
 *  Created on: Jun 12, 2018
 *      Author: TMK
 */


#include "textcaches.h"
#include "graphics.h"


SDL_Texture* TextCaches::getFpsTexture(std::string textToPrint){
	if(this->_fpsTextures.count(textToPrint) == 0){

		SDL_Color color = {255, 0, 0};

		SDL_Surface* textSurface = TTF_RenderText_Solid(this->_fpsFont, textToPrint.c_str(), color);

		if(textSurface == nullptr){
			std::cout << "deu erro no blittext textSurface: " << TTF_GetError() << std::endl;
		}

		this->_fpsTextures[textToPrint] = SDL_CreateTextureFromSurface(this->_graphicsAssociated->getRenderer(), textSurface);

		if(this->_fpsTextures[textToPrint] == nullptr){
			std::cout << "deu erro no blittext textTexture: " << TTF_GetError() << std::endl;
		}

		SDL_FreeSurface(textSurface);
	}
	return this->_fpsTextures[textToPrint];
}

TextCaches::TextCaches(){

}

TextCaches::TextCaches(Graphics &graphics):
		_graphicsAssociated(&graphics){
	this->_fpsFont = TTF_OpenFont("assets/impact.ttf", 22);

	if(this->_fpsFont == nullptr){
		std::cout << "deu erro Openfont: " << TTF_GetError() << std::endl;
	}
}

TextCaches::~TextCaches(){

}
