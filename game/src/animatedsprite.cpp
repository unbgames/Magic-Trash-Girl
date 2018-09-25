/*
 * animatedsprite.cpp
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#include "animatedsprite.h"
#include "graphics.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(){ // @suppress("Class members should be properly initialized")

}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate):
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	_dx(0),
	_dy(0),
	_timeToUpdate(timeToUpdate),
	_currentAnimationOnce(false),
	_currentAnimation(""),
	_frameIndex(0),
	_visible(true),
	_toBeDeleted(false)
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, ExVariables exVariables){
	std::vector<SDL_Rect> rectangles;

	if(frames < 1){
		std::cout << "error :: Tentativa de inserir anima��o sem frames" << std::endl;
	}

	for (int i=0; i<frames; i++){
		SDL_Rect newRect = { (i* width + x), y, width, height};
		rectangles.push_back(newRect);
	}
	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
	this->_exVariables.insert(std::pair<std::string, ExVariables>(name, exVariables));
}

void AnimatedSprite::resetAnimations(){
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once){

	this->_currentAnimationOnce = once;
	if(this->_currentAnimation != animation){
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible){
	this->_visible = visible;
}

bool AnimatedSprite::getVisible(){
	return this->_visible;
}

void AnimatedSprite::setToBeDeleted(bool toBeDeleted){
	this->_toBeDeleted = toBeDeleted;
}

bool AnimatedSprite::getToBeDeleted(){
	return this->_toBeDeleted;
}

void AnimatedSprite::stopAnimation(){
	this->_frameIndex = 0;
	this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(float elapsedTime) {
	Sprite::update();

	this->_timeElapsed += elapsedTime;
	if (this->_timeElapsed > this->_timeToUpdate) {
		this->_timeElapsed -= this->_timeToUpdate;
		if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1) {
			this->_frameIndex++;
		}else {
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->stopAnimation();
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics){

	if( (this->_x + this->_w < this->_graphicsAssociated->camera.getx()) ||
		(this->_x > this->_graphicsAssociated->camera.getx() + this->_graphicsAssociated->windowWidth) ||
		(this->_y + this->_h < this->_graphicsAssociated->camera.gety()) ||
		(this->_y > this->_graphicsAssociated->camera.gety() + this->_graphicsAssociated->windowHeight)){
		return;
	}

	if( this->_visible){
		SDL_Rect destinationRectangle;
		destinationRectangle.x = this->_x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = this->_y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_w;
		destinationRectangle.h = this->_h;

		SDL_Rect sourceRect = (this->_animations[this->_currentAnimation])[this->_frameIndex];

		ExVariables exVarAux = this->_exVariables[this->_currentAnimation];

		graphics.blitSurface(this->_spriteSheet, &sourceRect, &destinationRectangle, exVarAux.angle, exVarAux.centerOfRotation, exVarAux.flipFlag);
	}
}

void AnimatedSprite::animationDone(std::string currentAnimation){

}

void AnimatedSprite::setPosition(float x, float y){

	this->_x = x;
	this->_y = y;

}

bool AnimatedSprite::checkColision(float posX, float posY, float width, float height, float desX, float desY){

	if(((this->_x >= posX) && (this->_x <= posX+width - 1)) && ((this->_y >= posY) && (this->_y <= posY + height - 1))){
		return true;
	}
	if(((this->_x + this->_w - 1 >= posX) && (this->_x + this->_w - 1 <= posX+width - 1)) && ((this->_y >= posY) && (this->_y <= posY + height - 1))){
		return true;
	}
	if(((this->_x >= posX) && (this->_x <= posX+width - 1)) && ((this->_y + this->_h - 1 >= posY) && (this->_y + this->_h - 1 <= posY + height - 1))){
		return true;
	}
	if(((this->_x + this->_w - 1 >= posX) && (this->_x + this->_w - 1 <= posX+width - 1)) && ((this->_y + this->_h - 1 >= posY) && (this->_y + this->_h - 1 <= posY + height - 1))){
		return true;
	}

	if(((posX >= this->_x) && (posX <= this->_x + this->_w - 1)) && ((posY >= this->_y) && (posY <= this->_y + this->_h - 1))){
		return true;
	}
	if(((posX+width - 1 >= this->_x) && (posX+width - 1 <= this->_x + this->_w - 1)) && ((posY >= this->_y) && (posY <= this->_y + this->_h - 1))){
		return true;
	}
	if(((posX >= this->_x) && (posX <= this->_x + this->_w - 1)) && ((posY + height - 1 >= this->_y) && (posY + height - 1 <= this->_y + this->_h - 1))){
		return true;
	}
	if(((posX+width - 1 >= this->_x) && (posX+width - 1 <= this->_x + this->_w - 1)) && ((posY + height - 1 >= this->_y) && (posY + height - 1 <= this->_y + this->_h - 1))){
		return true;
	}

	return false;
}

void AnimatedSprite::getPosSize(float* x, float* y, int* w, int* h){
	*x = this->_x;
	*y = this->_y;
	*w = this->_w;
	*h = this->_h;
}

void AnimatedSprite::getDes(float* dx, float *dy){
	*dx = this->_dx;
	*dy = this->_dy;
}

void AnimatedSprite::takeContextAction(std::string objectType){

	//std::cout << "context action   == " << objectType << std::endl;

}

void AnimatedSprite::resolveColision(std::string objectType){

	//std::cout << "colision with   == " << objectType << std::endl;

}

float AnimatedSprite::getPosX(){
	return this->_x;
}
float AnimatedSprite::getPosY(){
	return this->_y;
}
float AnimatedSprite::getW(){
	return this->_w;
}
float AnimatedSprite::getH(){
	return this->_h;
}
float AnimatedSprite::getCenterX(){
	return this->_x + this->_w/2;
}
float AnimatedSprite::getCenterY(){
	return this->_y + this->_h/2;
}

