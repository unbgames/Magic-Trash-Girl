/*
 * camera.cpp
 *
 *  Created on: May 23, 2018
 *      Author: TMK
 */

#include "camera.h"
#include "globals.h"
#include "graphics.h"

Camera::Camera(){ // @suppress("Class members should be properly initialized")

}

Camera::Camera(Graphics &graphics):
	folowPlayer(true),
	_graphicsAssociated(&graphics),
	_x(((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH))/2),
	_y(( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2){
}


void Camera::setx(int x){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) <= this->_graphicsAssociated->windowWidth){
		this->_x = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH)/2 - this->_graphicsAssociated->windowWidth/2;
	}else if(x < 0){
		this->_x = 0;
	}else if(x > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth){
		this->_x = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth;
	}else{
		this->_x = x;
	}


}
void Camera::sety(int y){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) <= this->_graphicsAssociated->windowHeight){
		this->_y = ( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2 - this->_graphicsAssociated->windowHeight/2;;
	}else if( y < 0){
		this->_y = 0;
	}else if(y > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight){
		this->_y = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight;
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
