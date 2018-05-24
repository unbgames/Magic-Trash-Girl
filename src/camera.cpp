/*
 * camera.cpp
 *
 *  Created on: May 23, 2018
 *      Author: TMK
 */

#include "camera.h"
#include "globals.h"
#include "graphics.h"

Camera::Camera(Graphics &graphics):
	_x(((background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH))/2),
	_y((background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH)/2),
	_graphicsAssociated(&graphics){
}


void Camera::setx(int x){

	if((background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) <= this->_graphicsAssociated->windowWidth){
		return;
	}

	if(x < this->_graphicsAssociated->windowWidth/2){
		this->_x = this->_graphicsAssociated->windowWidth/2;
	}else if(x > (background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth/2){
		this->_x = (background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth/2;
	}else{
		this->_x = x;
	}


}
void Camera::sety(int y){

	if((background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) <= this->_graphicsAssociated->windowHeight){
		return;
	}

	if( y < this->_graphicsAssociated->windowHeight/2){
		this->_y = this->_graphicsAssociated->windowHeight/2;
	}else if(y > (background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight/2){
		this->_y = (background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight/2;
	}else{
		this->_y = y;
	}

}

int Camera::getx(){
	return this->_x;
}
int Camera::gety(){
	return this->_y;
}
