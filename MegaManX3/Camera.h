#ifndef _Camera_H
#define _Camera_H

#include "ConstGlobals.h"
#include "Game.h"

class Camera {
private:
	int maxValue, minValue;


	bool lockLeft = false;
	bool lockTop = false;

	int state;

	bool aniSwitchState = false;
	bool enable = true;

	void switchState();


	void state1(int cameraX, int cameraY);
	void state2(int cameraX, int cameraY);
	void state3(int cameraX, int cameraY);
	void state4(int cameraX, int cameraY);
	void state5(int cameraX, int cameraY);
	void state6(int cameraX, int cameraY);
	void state7(int cameraX, int cameraY);
public:
	void setEnable(bool value) { this->enable = value; }
	Viewport viewport;
	Rect world;

	Camera(int x, int y, int width, int height);

	void update(int x, int y);

	void nextState();

	void setSizeWorld(int x,int y,int width,int height);

	const Point transform(const int& x,const int& y) const;
	//D3DXVECTOR3 transformToViewport(int x, int y);// transform to viewport
};

#endif // _Camera_H_

