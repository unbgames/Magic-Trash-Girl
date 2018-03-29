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

	void update(int elapsedTime);

	void draw(Graphics &graphics, int x, int y);

	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

protected:

	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	void resetAnimations();

	void stopAnimation();

	void setVisible(bool visible);

	virtual void animationDone(std::string currentAnimation);

	//virtual void setupAnimations() = 0;

private:

	std::map<std::string, std::vector<SDL_Rect>> _animations;
	std::map<std::string, Vector2> _offsets;

	unsigned int _frameIndex;
	double _timeElapsed = 0;
	bool _visible;

};



#endif /* SOURCE_HEADERS_ANIMATEDSPRITE_H_ */
