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
	const float WALK_SPEED = 0.1f;
	const float JUMP_SPEED = 0.1f;
	const float FALL_SPEED = 0.1f;

	const float PLAYER_START_X = 100;
	const float PLAYER_START_Y = 300;

	const float PROJECTILE_SPEED = 0.3f;
}

namespace globals{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGTH = 576;

	const std::string WINDOW_NAME = "Trash Girl";
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
//	BUBLE,
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
