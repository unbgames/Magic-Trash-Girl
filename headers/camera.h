/*
 * camera.h
 *
 *  Created on: May 23, 2018
 *      Author: TMK
 */

class Camera{
public:

	Camera();

	void setx(int x);
	void sety(int y);

	int getx();
	int gety();

private:

	int _x, _y;
};


