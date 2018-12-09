#ifndef _KeyController_H_
#define _KeyController_H_
#include "CTime.h"
#include "GameObject.h"
#include "Brick.h"
enum StatusJump
{
	Jump = 1,
	Kick = 2,
	None = 0,
	Fall = -1,
	Slide = -2
};
enum class Arrow
{
	Left = -1,
	None = 0,
	Right = 1,
	Two = 2
};
class KeyController
{
private:
	GameObject* main;
	Brick* wall;

	int width = 0;
	int height = 0;

	bool toLeft = false;

	//arow
	int pressArrow = 0; // left right
	Arrow arrow = Arrow::None;

	bool pressZ = false;
	bool pressX = false;
	bool pressC = false;

	//stand
	bool onFloor = false;
	bool isStand = false;// don't direction
	bool isWall = false;//near wall

	bool isHoldLeft = false;
	bool isHoldRight = false;
	bool isWallLeft = false;//direction wall
	// run
	bool isRun = false; // change direction



	// jum

	// 1 jum
	// 2 kick
	// -1 fall
	// -2 slide
	StatusJump statusJump = StatusJump::Jump;

	bool onAir = false;
	CTime timeJump = CTime(250);
	CTime timeKick = CTime(150);

	//dash
	bool isDash = false;
	CTime timeDash = CTime(600);

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

	void updateState();
	void updateVx();
	void _update();
public:
	KeyController(GameObject* megaman, bool left) { this->main = megaman, this->toLeft = left; };
	~KeyController() {};


	bool isKeyZ();
	bool isKeyX();
	bool iskeyC();

	bool isLeft();

	void update();
	void update(float nx, float ny);
	//cancel animation
	//jum
	void stopJumpRunning();
	void stopJump();
	void stopFall(); // 
	void stopSlideWall();

	void stopFallOrSlide();


	void stopDashRunning();
	void stopDash();

	void stopRun();
	void stopShoot();

	void setNearWall(bool, Brick*);

	//jump
	void jump();
	void kickWall();
	//wall


	void addKeyZ();
	void addKeyX();
	void addKeyC();
	void addKeyArrow(bool isLeft);

	void removeKeyZ();
	void removeKeyX();
	void removeKeyC();
	void removeKeyArrow(bool isLeft);
	
	void getSize(int&width, int& height);
	UINT getState(bool& isLeft);
};

#endif //! _KeyController_H_