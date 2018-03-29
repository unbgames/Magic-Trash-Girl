/*
 * globlas.h
 *
 *  Created on: Mar 29, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_GLOBALS_H_
#define SOURCE_HEADERS_GLOBALS_H_

namespace globals{
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGTH = 600;
}

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
