/*
 * game.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GAME_H_
#define SOURCE_HEADERS_GAME_H_

#include "animatedsprite.h"
#include <vector>
#include "player.h"
#include "input.h"

class Graphics;

class Game{
public:

	Game();

	~Game();

private:

	void gameLoop();

	void draw(Graphics &graphics);

	void update(float elapsedtime);

	std::vector<AnimatedSprite> spritesToDraw;

	Player _player;

	Input _input;

};



#endif /* SOURCE_HEADERS_GAME_H_ */
