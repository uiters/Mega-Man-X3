#ifndef _Camera_H
#define _Camera_H

#include "ConstGlobals.h"
#include "Game.h"
#include "Brick.h"
#include "Elevator.h"

class Brick;

class Camera {
private:
	int maxValue, minValue;

	void(Camera::*state) (int, int);

	int nAnimation = 1;
	Brick* blockBackward; //Block ,main backward 

	bool lockLeft = false;
	bool lockTop = false;

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
	void state8(int cameraX, int cameraY);
	void state9(int cameraX, int cameraY);
	void state10(int cameraX, int cameraY);

	void nextAnimation();
public:
	Viewport viewport;

	Camera(int x, int y, int width, int height);

	void update(int x, int y);
	
	const Point transform(const int& x,const int& y) const;

public:
	Brick* getBlock() { return blockBackward; }
	int getState() { return nAnimation; }

public:
	void setEnable(bool value) { this->enable = value; }
};

#endif // _Camera_H_

