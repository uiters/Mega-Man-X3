#include "KeyController.h"
#include "Debugs.h"
#pragma region Check Key
bool KeyController::isKeyZ()
{
	return pressZ;
}

bool KeyController::isKeyX()
{
	return pressX;
}

bool KeyController::iskeyC()
{
	return pressC;
}

bool KeyController::isLeft() 
{
	return toLeft;
}
#pragma endregion

#pragma region Update

void KeyController::update()
{
	_update();
}

void KeyController::update(float nx, float ny)
{
	_update();

	if (ny < 0) stopFall();
	else if (ny > 0) state = fall, stopJump();

	if (nx != 0)
	{
		state = stand;
		isDash = false;
		isRun = false;
	}
}

void KeyController::_update()
{
	updateDash();
	updateJump();
	updateShoot();
	updateRun();

	updateState();
	updateVx();
}

void KeyController::updateState()
{
	if (isDash)
	{
		state = dash;
		stateShoot = dash_shoot;
		width = Dash_Shoot_Width;
		height = Dash_Shoot_Height;
		return;
	}
	if (onAir)
	{
		switch (statusJump)
		{
		case StatusJump::Jump:
		case StatusJump::Kick:
			state = MegaManAnimation::jump;
			stateShoot = jump_shoot;
			width = Jump_Shoot_Width;
			height = Jump_Shoot_Height;
			main->speed.vy = -0.25f;

		case StatusJump::Fall:
			state = MegaManAnimation::fall;
			stateShoot = fall_shoot;
			width = Fall_Shoot_Width;
			height = Fall_Shoot_Height;
			break;

		case StatusJump::Slide:
			state = MegaManAnimation::slide;
			stateShoot = slide_shoot;
			width = Slide_Shoot_Width;
			height = Slide_Shoot_Height;
			break;
		default:
			break;
		}
		return;
	}
	if (isRun && !isStand)
	{
		state = MegaManAnimation::run;
		stateShoot = run_shoot;
		width = Run_Shoot_Width;
		height = Run_Shoot_Height;
	}
	else
		state = MegaManAnimation::stand,
		stateShoot = shoot,
		width = Stand_Shoot_Width,
		height = Stand_Shoot_Height;
}

void KeyController::updateVx()
{
	if (isDash)
		main->speed.vx = toLeft ? -0.25f : 0.25f;
	else
		if (isRun && !isStand)
		{
			main->speed.vx = toLeft ? -0.15f : 0.15f;
		}
		else
			main->speed.vx = 0;

}
#pragma endregion

#pragma region Shoot
void KeyController::addKeyZ()
{
	pressZ = true;
	timePressZ.start();
}

void KeyController::removeKeyZ()
{
	pressZ = false;
	isShot = true;
	timePressZ.stop();
	timeShoot.start();
}

void KeyController::stopShoot() 
{
	isShot = false;
	timePressZ.stop();
	timeShoot.stop();
}

void KeyController::updateShoot()
{
	if (pressZ)
		timePressZ.update();
	if(isShot)
	{
		if (timeShoot.isRunning())
		{
			timeShoot.update();
		}
		else
			isShot = false;
	}
}

#pragma endregion

#pragma region Jump

void KeyController::addKeyX()
{
	stopDash();
	pressX = true;

	if (onAir)
	{
		if (isWall)
			kickWall();
	}
	else
	{
		jump();
	}
}

void KeyController::removeKeyX()
{
	pressX = false;
	stopJump();
}

void KeyController::stopJumpRunning()
{
	statusJump = StatusJump::Fall;
	timeJump.stop();
}

void KeyController::stopJump()
{
	if (timeJump.isRunning())
	{
		statusJump = StatusJump::Fall;
		timeJump.stop();
	}
}

void KeyController::updateJump()
{
	if (timeJump.isRunning())
	{
		timeJump.update();
	}
	else if(onAir)
	{
		if (StatusJump::Jump == statusJump || statusJump == StatusJump::Kick) 
			stopJumpRunning();

		if (statusJump == StatusJump::Fall && isWall && isWallLeft == toLeft)
		{
			statusJump = StatusJump::Slide;
			return;
		}

		if (statusJump == StatusJump::Slide && !isWall && isWallLeft != toLeft)
			statusJump = StatusJump::Fall;
	}
}

void KeyController::stopFall() 
{
	if (statusJump == StatusJump::Fall)
	{
		timeJump.stop();
		statusJump = StatusJump::None;
		onAir = false;
		onFloor = true;
	}
}

void KeyController::stopSlideWall()
{
	if (statusJump == StatusJump::Slide)
	{
		timeJump.stop();
		statusJump = StatusJump::None;
		onAir = false;
		onFloor = true;
	}
}

void KeyController::stopFallOrSlide()
{
	stopFall();
	stopSlideWall();
}

void KeyController::jump()
{
	timeJump.start();
	statusJump = StatusJump::Jump;

	onAir = true;
	onFloor = false;
}

void KeyController::kickWall()
{
	timeJump.start();
	statusJump = StatusJump::Kick;

	main->x += toLeft ? 20 : -20;
}

#pragma endregion

#pragma region Dash
void KeyController::addKeyC()
{
	if (onAir || isWall) return;//----
	pressC = true;
	isDash = true;
	timeDash.start();
}

void KeyController::removeKeyC()
{
	pressC = false;
	stopDash();
}

void KeyController::stopDashRunning()
{
	isDash = false;
	timeDash.stop();
}

void KeyController::stopDash()
{
	if (timeDash.isRunning())
	{
		isDash = false;
		timeDash.stop();
	}
}

void KeyController::updateDash()
{
	if (timeDash.isRunning())
	{
		if (onAir)
		{
			stopDashRunning();
			statusJump = StatusJump::Fall;
			return;
		}
		if (isWall)
		{
			stopDashRunning();
			return;
		}
		timeDash.update();
	}
	else // time up
	{
		if (isDash) isDash = false;
	}
}
#pragma endregion

#pragma region Arrow
void KeyController::addKeyArrow(bool isLeft)
{
	pressArrow += 1;
	if (pressArrow == 2) // stand
	{
		arrow = Arrow::Two;
		isRun = false;
		isHoldLeft = isHoldRight = false;
		isStand = true;//stand
	}
	else // run
	{
		if (isLeft != toLeft) // toleft == left or toRight ==right
			stopDash(); //cancel dash
		isLeft ? arrow = Arrow::Left : arrow = Arrow::Right;
		toLeft = isLeft;
		isRun = true;
		isStand = false;
	}
}

void KeyController::removeKeyArrow(bool isLeft)
{
	pressArrow -= 1;
	if (pressArrow == 1) //run
	{
		isLeft ? arrow = Arrow::Right : arrow = Arrow::Left;
		toLeft = !isLeft;
		if (isLeft != toLeft) stopDash(); //cancel dash
		isRun = true; //run
		isStand = false;
	}
	else //stand
	{
		isStand = true;
		arrow = Arrow::None;
		isRun = false;
		isHoldLeft = isHoldRight = false;
	}
	
}

void KeyController::stopRun()
{
	if (isRun)
	{
		isRun = false;
		isStand = true;
	}
}

void KeyController::updateRun()
{
	if (isRun && !isWall || isWallLeft != toLeft)
		isStand = false;
	else
		isStand = true;
}

void KeyController::setNearWall(bool isTrue, Brick* wall)
{
	isWall = isTrue;
	this->isWall = wall;
}

#pragma endregion



void KeyController::getSize(int & width, int & height)
{
	width = this->width;
	height = this->height;
}

UINT KeyController::getState(bool& isLeft)
{
	isLeft = toLeft;
	
	return isShot ? stateShoot : state;
}
