/*
 * camera.cpp
 *
 *  Created on: May 23, 2018
 *      Author: TMK
 */

#include "camera.h"
#include "globals.h"

Camera::Camera():
	_x(((background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH))/2),
	_y((background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH)/2){

}


void Camera::setx(int x){

	if((background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) <= globals::SCREEN_WIDTH){
		return;
	}

	if(x < globals::SCREEN_WIDTH/2){
		this->_x = globals::SCREEN_WIDTH/2;
	}else if(x > (background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) - globals::SCREEN_WIDTH/2){
		this->_x = (background_blocks_constants::NUMBER_BLOCKS_LINE * background_blocks_constants::BLOCK_WIDTH) - globals::SCREEN_WIDTH/2;
	}else{
		this->_x = x;
	}


}
void Camera::sety(int y){

	if((background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) <= globals::SCREEN_HEIGTH){
		return;
	}

	if( y < globals::SCREEN_HEIGTH/2){
		this->_y = globals::SCREEN_HEIGTH/2;
	}else if(y > (background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) - globals::SCREEN_HEIGTH/2){
		this->_y = (background_blocks_constants::NUMBER_BLOCKS_COLUMN * background_blocks_constants::BLOCK_HEIGTH) - globals::SCREEN_HEIGTH/2;
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
