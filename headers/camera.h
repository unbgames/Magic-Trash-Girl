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

	Camera();
	Camera(Graphics &graphics);

	void update(float elapsedTime);

	void smoothSetX(int x);
	void smoothSetY(int y);

	void hardSetX(int x);
	void hardSetY(int y);

	int getx();
	int gety();

	bool folowPlayer;

private:

	Graphics* _graphicsAssociated;

	int _x, _y, _targetX, _targetY;

	float _dx, _dy;

};

#endif /* SOURCE_HEADERS_CAMERA_H_ */

