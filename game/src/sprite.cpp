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
		_angle(0),
		_centerOfRotation(nullptr),
		_flipFlag(SDL_FLIP_NONE),
		_graphicsAssociated(&graphics)
{
	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = widht;
	this->_sourceRect.h = height;

	this->_spriteSheet = this->_graphicsAssociated->loadTexture(filePath);

	if(this->_spriteSheet == NULL){
		std::cout<<"\nError: Nao conseguiu carregar imagem :: " <<  SDL_GetError() << std::endl;
	}
}

Sprite::~Sprite(){

}

void Sprite::draw(Graphics &graphics, int x, int y){
	SDL_Rect destinationRectangle = {x, y, this->_sourceRect.w, this->_sourceRect.h};
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle, this->_angle, this->_centerOfRotation, this->_flipFlag);
}

void Sprite::update(){

}
