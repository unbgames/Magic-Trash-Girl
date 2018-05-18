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
#include <memory>

class Graphics;

class Game{
public:

	Game();

	~Game();

	static Game& getInstance();

	void addNewSpriteToDraw(std::unique_ptr<AnimatedSprite> sprite);

private:

	static Game* _instance;

	void gameLoop();

	void draw(Graphics &graphics);

	void update(float elapsedtime);

	std::vector<std::unique_ptr<AnimatedSprite>> _spritesToDraw;

	std::unique_ptr<AnimatedSprite> spriteToDraw;

	Player _player;

	Input _input;

};



#endif /* SOURCE_HEADERS_GAME_H_ */
