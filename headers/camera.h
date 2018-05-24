/*
 * camera.h
 *
 *  Created on: May 23, 2018
 *      Author: TMK
 */

#ifndef SOURCE_HEADERS_CAMERA_H_
#define SOURCE_HEADERS_CAMERA_H_

class Graphics;

class Camera{
public:

	Camera(Graphics &graphics);

	void setx(int x);
	void sety(int y);

	int getx();
	int gety();

private:

	int _x, _y;

	Graphics* _graphicsAssociated;
};

#endif /* SOURCE_HEADERS_CAMERA_H_ */

