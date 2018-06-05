/*
 * animatedsprite.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_ANIMATEDSPRITE_H_
#define SOURCE_HEADERS_ANIMATEDSPRITE_H_

#include <map>
#include <string>
#include <vector>
#include "globals.h"
#include "sprite.h"

class Graphics;

class AnimatedSprite : public Sprite{
public:

	AnimatedSprite();

	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);

	void playAnimation(std::string animation, bool once = false);

	virtual void update(float elapsedTime);

	virtual void draw(Graphics &graphics);

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset, ExVariables exVariables = ExVariables());

	bool getToBeDeleted();

	void setPosition(float x, float y);

	void setVisible(bool visible);
	bool getVisible();

	virtual std::string getObjectType() = 0;

	bool checkColision(float posX, float posY, float width, float height, float desX, float desY);

	void getPosSize(float* x, float* y, int* w, int* h);

	void getDes(float* dx, float *dy);

	virtual void takeContextAction(std::string objectType);

	float getPosX();
	float getPosY();
	float getW();
	float getH();

protected:

	float _dx, _dy;

	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void resetAnimations();

	void stopAnimation();

	void setToBeDeleted(bool toBeDeleted);

	virtual void animationDone(std::string currentAnimation);

	virtual void setupAnimations() = 0;

private:

	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;
	std::map<std::string, ExVariables> _exVariables;

	unsigned int _frameIndex;
	double _timeElapsed = 0;
	bool _visible;
	bool _toBeDeleted;

};



#endif /* SOURCE_HEADERS_ANIMATEDSPRITE_H_ */
