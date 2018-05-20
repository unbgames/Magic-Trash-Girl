/*
 * globlas.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GLOBALS_H_
#define SOURCE_HEADERS_GLOBALS_H_

#include <string>

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float JUMP_SPEED = 0.2f;
	const float FALL_SPEED = 0.2f;

	const float PLAYER_START_X = 100;
	const float PLAYER_START_Y = 500;

	const float PROJECTILE_SPEED = 0.3f;
}

namespace globals{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGTH = 600;

	const std::string WINDOW_NAME = "Trash Girl";
}

enum Direction{
	LEFT,
	RIGHT,
	UP,
	DOWN,
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

#endif /* SOURCE_HEADERS_GLOBALS_H_ */
