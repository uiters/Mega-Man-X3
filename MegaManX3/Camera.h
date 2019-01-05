#ifndef _Camera_H_
#define _Camera_H_
#pragma once
#include "ConstGlobals.h"
#include "Game.h"
#include "Block.h"
#include "Elevator.h"

class Block;

class Camera {
private:
	int maxValue, minValue;

	void(Camera::*state) (int, int);

	int nAnimation = 1;
	Block* blockBackward; //Block ,main backward 

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
	Block* getBlock() { return blockBackward; }
	int getState() { return nAnimation; }

public:
	void setEnable(bool value) { this->enable = value; }
};

#endif // _Camera_H_

