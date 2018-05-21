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
	_timeToUpdate(timeToUpdate),
	_currentAnimationOnce(false),
	_currentAnimation(""),
	_frameIndex(0),
	_visible(true),
	_toBeDeleted(false)
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, ExVariables exVariables){
	std::vector<SDL_Rect> rectangles;
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
		}
		else {
			if (this->_currentAnimationOnce == true) {
				this->setVisible(false);
			}
			this->stopAnimation();
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics){

	if( this->_visible){
		SDL_Rect destinationRectangle;
		destinationRectangle.x = this->_x + this->_offsets[this->_currentAnimation].x;
		destinationRectangle.y = this->_y + this->_offsets[this->_currentAnimation].y;
		destinationRectangle.w = this->_sourceRect.w;
		destinationRectangle.h = this->_sourceRect.h;

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
