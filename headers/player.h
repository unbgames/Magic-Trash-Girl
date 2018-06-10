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
	void activateVacuum();
	void takeContextAction(std::string objectType);

	void animationDone(std::string currentAnimation);

	void setupAnimations();

	void setTimeForFrames(double newTime);
	double getTimeForFrames();

	void setPosition(float x, float y);

	std::string getObjectType();

	Direction getFacing();

	bool getIsSwiming();

	void resolveColision(std::string objectType);

private:

	static int playercount;

	void _checkBackgroundColision(float elapsedTime);

	void _correctionBackgroundColision();

	Direction _facing;
	Direction _idleFacing;
	bool _isAirborne;
	bool _isSwiming;

	bool _startJump;

	bool _invulnerable;
	float _invulnerableTimer;
	float _invulnerableBlinkTimer;

	int _hp;

};



#endif /* SOURCE_HEADERS_PLAYER_H_ */
