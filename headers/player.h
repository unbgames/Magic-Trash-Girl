/*
 * player.h
 *
 *  Created on: Apr 17, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_PLAYER_H_
#define SOURCE_HEADERS_PLAYER_H_

#include "animatedsprite.h"
#include "vacuumcone.h"

class Player : public AnimatedSprite{
public:
	Player();

	Player(Graphics &graphics, float posX, float posY);

	~Player();

	void update(float elapsedTime);
	void draw(Graphics &graphics);

	void moveLeft();
	void moveRight();
	void stopMoving();
	void jump();
	void lookUp();
	void lookDown();
	void startVacuum();
	void stopVacuum();
	void bubble();

	void getPosSize(float* x, float* y, float* w, float* h);


	void animationDone(std::string currentAnimation);

	void setupAnimations();

	void setTimeForFrames(double newTime);
	double getTimeForFrames();

private:

	float _dx, _dy;

	Direction _facing;
	Direction _idleFacing;
	bool _isAirborne;

	bool _startJump;

	VacuumCone _vCone;

};



#endif /* SOURCE_HEADERS_PLAYER_H_ */
