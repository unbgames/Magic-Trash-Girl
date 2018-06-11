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
#include <SDL2/SDL_gamecontroller.h>

namespace player_constants {
	const float WALK_SPEED = 0.4f;
	const float NORMAL_JUMP_SPEED = -0.8f;
	const float BUBLE_JUMP_SPEED = -1.2f;
	const float WATER_JUMP_SPEED =  -0.2f;
	const float FALL_ACELERATION = 0.002f;
	const float FALL_ACELERATION_IN_WATER = 0.0002f;
	const float MAX_FALL_SPEED_ON_WATER = 0.3f;
	const float MAX_FALL_SPEED = 1.2f;

	const float PLAYER_START_X = 130;
	const float PLAYER_START_Y = 72;

	const float PROJECTILE_SPEED = 0.8f;

	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGTH = 48;

	const int CONE_WIDTH = 32;
	const int CONE_HEIGTH = 32;

	const int INVULNERABILITY_TIME = 2000;
	const int INVULNERABILITY_BLINK_TIME = 100;
}

namespace vacuum_constants{
	const int VACUUM_WIDTH = 48;
	const int VACUUM_HEIGTH = 24;

	const float FLOAT_SPEED = 0.4f;
}

namespace globals{
	const int INITIAL_SCREEN_WIDTH = 1024;
	const int INITIAL_SCREEN_HEIGTH = 576;

	const std::string WINDOW_NAME = "Trash Girl";

	const float SMOOTH_CAMERA_VELOCITY = 0.3f;
	const float SMOOTH_CAMERA_TIMER_MAX = 200;

	const float FALL_ACELERATION = 0.002f;
	const float MAX_FALL_SPEED = 1.2f;
}

namespace background_blocks_constants {
	const int BLOCK_WIDTH = 64;
	const int BLOCK_HEIGTH = 64;

	const int INITIAL_NUMBER_BLOCKS_LINE = 34; //globals::SCREEN_WIDTH / BLOCK_WIDTH;
	const int INITIAL_NUMBER_BLOCKS_COLUMN = 34 ;//globals::SCREEN_HEIGTH / BLOCK_HEIGTH;

	const int NUMBER_BLOCKS_LINE_SECTORS = 16;
	const int NUMBER_BLOCKS_COLUMN_SECTORS = 16;

	const int NUMBER_SECTORS_LINE = 8;
	const int NUMBER_SECTORS_COLUMN = 8;

	const int BLOCK_BORDER_TOP_BOT_SIZE = BLOCK_WIDTH/4;
	const int BLOCK_BORDER_RIGHT_LEFT_SIZE = BLOCK_HEIGTH/4;
}

namespace enemy_constants {
	const int SPYDER_WIDTH = 48;
	const int SPYDER_HEIGHT = 32;
	const int SPIDER_HP = 100;
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
	WATER,
	OUTOFBONDS
};

enum MapObjectType{
	PLAYER_START_POSITION, 		// 0
	PORTAL_TO_NEXT_RANDOM_LEVEL,// 1
	RAT, 					// 2

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

enum xbox360GamepadMaping{
	A = 0,
	B = 1,
	X = 2,
	Y = 3,
	directionalUp = 11,
	directionalDown = 12,
	directionalRight = 14,
	directionalLeft = 13,
	start = 6
};

#endif /* SOURCE_HEADERS_GLOBALS_H_ */
