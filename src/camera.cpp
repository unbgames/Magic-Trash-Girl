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
	_delayFlag(true),
	_delayTimer(0),
	_graphicsAssociated(&graphics),
	_x(((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH))/2),
	_y(( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2),
	_targetX(((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH))/2),
	_targetY(( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2),
	_dx(0),
	_dy(0){

}


void Camera::hardSetX(int x){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) <= this->_graphicsAssociated->windowWidth){
		this->_x = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH)/2 - this->_graphicsAssociated->windowWidth/2;
	}else if(x < 0){
		this->_x = 0;
	}else if(x > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth){
		this->_x = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth;
	}else{
		this->_x = x;
	}

	this->_targetX = this->_x;

	this->_targetY = this->_y;

	this->_dx = 0;

	this->_dy = 0;
}
void Camera::hardSetY(int y){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) <= this->_graphicsAssociated->windowHeight){
		this->_y = ( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2 - this->_graphicsAssociated->windowHeight/2;;
	}else if( y < 0){
		this->_y = 0;
	}else if(y > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight){
		this->_y = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight;
	}else{
		this->_y = y;
	}

	this->_targetX = this->_x;

	this->_targetY = this->_y;

	this->_dx = 0;

	this->_dy = 0;

}

void Camera::smoothSetX(int x){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) <= this->_graphicsAssociated->windowWidth){
		this->_targetX = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH)/2 - this->_graphicsAssociated->windowWidth/2;
	}else if(x < 0){
		this->_targetX = 0;
	}else if(x > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth){
		this->_targetX = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksLine() * background_blocks_constants::BLOCK_WIDTH) - this->_graphicsAssociated->windowWidth;
	}else{
		this->_targetX = x;
	}

}

void Camera::smoothSetY(int y){

	if((this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) <= this->_graphicsAssociated->windowHeight){
		this->_targetY = ( this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH)/2 - this->_graphicsAssociated->windowHeight/2;;
	}else if( y < 0){
		this->_targetY = 0;
	}else if(y > (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight){
		this->_targetY = (this->_graphicsAssociated->getGameAssociated()->getCurrentNumberBlocksColumn() * background_blocks_constants::BLOCK_HEIGTH) - this->_graphicsAssociated->windowHeight;
	}else{
		this->_targetY = y;
	}

}

void Camera::update(float elapsedTime){

	this->_dx = (this->_targetX > this->_x)? globals::SMOOTH_CAMERA_VELOCITY : -globals::SMOOTH_CAMERA_VELOCITY;
	this->_dy = (this->_targetY > this->_y)? globals::SMOOTH_CAMERA_VELOCITY : -globals::SMOOTH_CAMERA_VELOCITY;

	if((this->_y == this->_targetY) && (this->_x == this->_targetX)){
		this->_delayTimer = 0;
	}

	if(((this->_y != this->_targetY) || (this->_x != this->_targetX)) && this->_delayFlag == true){
		this->_delayTimer += elapsedTime;
 		if(this->_delayTimer >= globals::SMOOTH_CAMERA_TIMER_MAX){
			this->_delayFlag = false;
			this->_delayTimer = 0;
		}
	}

	if(this->_delayFlag == true){
		return;
	}

	this->_x += this->_dx * elapsedTime;
	this->_y += this->_dy * elapsedTime;

	if(std::abs(this->_x - this->_targetX) > 128){
		this->_x = (this->_dx > 0)? this->_targetX - 128 : this->_targetX + 128;
	}
	if(std::abs(this->_y - this->_targetY) > 128){
		this->_y = (this->_dy > 0)? this->_targetY - 128 : this->_targetY + 128;
	}

	if(this->_dx > 0){
		if(this->_x >= this->_targetX){
			this->_x = this->_targetX;
			this->_dx = 0;
		}
	}else{
		if(this->_x <= this->_targetX){
			this->_x = this->_targetX;
			this->_dx = 0;
		}
	}

	if(this->_dy > 0){
		if(this->_y >= this->_targetY){
			this->_y = this->_targetY;
			this->_dy = 0;
		}
	}else{
		if(this->_y <= this->_targetY){
			this->_y = this->_targetY;
			this->_dy = 0;
		}
	}

	if((this->_y == this->_targetY) && (this->_x == this->_targetX)){
		this->_delayFlag = true;
	}
}

int Camera::getx(){
	return this->_x;
}
int Camera::gety(){
	return this->_y;
}
