/*
 * globlas.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GLOBALS_H_
#define SOURCE_HEADERS_GLOBALS_H_

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float NORMAL_JUMP_SPEED = -0.7f;
	const float BUBLE_JUMP_SPEED = -1.1f;
	const float FALL_ACELERATION = 0.002f;

	const float PLAYER_START_X = 130;
	const float PLAYER_START_Y = 72;

	const float PROJECTILE_SPEED = 0.5f;

	const int PLAYER_WIDTH = 26;
	const int PLAYER_HEIGTH = 42;

	const int CONE_WIDTH = 42;
	const int CONE_HEIGTH = 42;
}

namespace globals{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGTH = 576;



	const std::string WINDOW_NAME = "Trash Girl";
}

namespace background_blocks_constants {
	const int BLOCK_WIDTH = 64;
	const int BLOCK_HEIGTH = 64;

	const int NUMBER_BLOCKS_LINE = 20; //globals::SCREEN_WIDTH / BLOCK_WIDTH;
	const int NUMBER_BLOCKS_COLUMN = 20 ;//globals::SCREEN_HEIGTH / BLOCK_HEIGTH;
}

enum Direction{
	LEFT,
	RIGHT,
	UP,
	DOWN,
};

enum BlockType{
	NONE,
	BREAKABLE,
	UNBREAKABLE,
	BUBLE,
//	OUTOFBONDS
};


struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0)
	{}
	Vector2(int x, int y):
		x(x), y(y)
	{}
	Vector2 zero(){
		return Vector2(0, 0);
	}
};

struct ExVariables{
	double angle;
	SDL_Point* centerOfRotation;
	SDL_RendererFlip flipFlag;

	ExVariables() :
		angle(0),
		centerOfRotation(nullptr),
		flipFlag(SDL_FLIP_NONE)
	{}

	ExVariables(double angleIn, SDL_Point* centerIn, SDL_RendererFlip flipIn) :
		angle(angleIn),
		centerOfRotation(centerIn),
		flipFlag(flipIn)
	{}

};

#endif /* SOURCE_HEADERS_GLOBALS_H_ */
