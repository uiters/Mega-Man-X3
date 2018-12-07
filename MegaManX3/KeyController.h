#ifndef _KeyController_H_
#define _KeyController_H_
#include "CTime.h"

class KeyController
{
private:
	bool toLeft = false;

	int pressArrow = 0; // left right
	bool left = false;
	bool right = false;

	bool pressZ = false;
	bool pressX = false;
	bool pressC = false;

	//stand
	bool onFloor = false;
	bool isStand = false;

	// run
	bool isRun = false;

	// hold
	bool isHoldLeft = false;
	bool isHoldRight = false;

	// jum
	bool isJump = false;
	bool isFall = false;
	bool onAir = false;
	
	CTime timeJump = CTime(600);
	//dash
	bool isDash = false;
	CTime timeDash = CTime(800);

	//shoot
	bool isShot = false;
	CTime timeShoot = CTime(400);
	CTime timePressZ = CTime();

	UINT state = 0;
	UINT stateShoot = shoot;

	void updateShoot();
	void updateJump();
	void updateDash();
	void updateRun();
public:
	KeyController(bool left) { this->toLeft = left; };
	~KeyController() {};


	bool isKeyZ();
	bool isKeyX();
	bool iskeyC();

	bool isLeft();

	void update();

	//cancel animation
	void stopJump();
	void stopDash();
	void stopRun();

	void stopShoot();
	void stopFall();

	void addKeyZ();
	void addKeyX();
	void addKeyC();
	void addKeyArrow(bool isLeft);

	void removeKeyZ();
	void removeKeyX();
	void removeKeyC();
	void removeKeyArrow(bool isLeft);

	

	UINT getState(bool& isLeft);
};

#endif //! _KeyController_H_