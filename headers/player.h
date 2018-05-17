/*
 * player.h
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_PLAYER_H_
#define SOURCE_HEADERS_PLAYER_H_

#include "animatedsprite.h"

class Player : public AnimatedSprite{
public:
	Player();

	Player(Graphics &graphics, float posX, float posY);

	~Player();

	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft();
	void moveRight();
	void stopMoving();
	void jump();
//	void lookUP();
//	void lookDown();
//	void vacuum();
//	void bubble();


	void animationDone(std::string currentAnimation);

	void setupAnimations();

	void setTimeForFrames(double newTime);
	double getTimeForFrames();

private:

	float _dx, _dy;

	Direction _facing;
	bool _isAirborne;

	bool _startJump;
};



#endif /* SOURCE_HEADERS_PLAYER_H_ */