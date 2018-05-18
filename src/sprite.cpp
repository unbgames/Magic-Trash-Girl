/*
 * sprite.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#include <iostream>
#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite(){ // @suppress("Class members should be properly initialized")

}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int widht, int height, float posX, float posY):
		_x(posX),
		_y(posY),
		_w(widht),
		_h(height),
		_graphicsAssociated(&graphics)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = widht;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
	if(this->_spriteSheet == NULL){
		std::cout<<"\nError: Nao conseguiu carregar imagem";
	}
}

Sprite::~Sprite(){

}

void Sprite::draw(Graphics &graphics, int x, int y){
	SDL_Rect destinationRectangle = {x, y, this->_sourceRect.w, this->_sourceRect.h};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update(){

}
