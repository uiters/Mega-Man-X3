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


void KeyController::update()
{
	updateDash();
	updateJump();
	updateShoot();
	updateRun();
}

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
	else 
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
	if (onAir) return;
	
	timeDash.stop();
	pressX = true;

	timeJump.start();
	isJump = true;
	isFall = false;
	onAir = true;
}

void KeyController::removeKeyX()
{
	pressX = false;
	stopJump();
}

void KeyController::stopJump()
{
	if (timeJump.isRunning())
	{
		isFall = true;
		isJump = false;
		timeJump.stop();
		state = fall;
	}
}

void KeyController::updateJump()
{
	if (timeJump.isRunning())
	{
		state = jump; //current jump
		stateShoot = jump_shoot;
		timeJump.update();
	}
	else 
		if (isJump)
		{
			isJump = false;
			isFall = true;
			state = fall;
			stateShoot = fall_shoot;
		}
}

void KeyController::stopFall() 
{
	if (isFall)
	{
		isJump = false;
		isFall = false;
		onAir = false;
		isStand = true;
	}
}
#pragma endregion

#pragma region Dash
void KeyController::addKeyC()
{
	if (onAir) return;
	pressC = true;
	timeDash.start();
	isDash = true;
}

void KeyController::removeKeyC()
{
	pressC = false;
	if (timeDash.isRunning()) 
	{
		isDash = false;
		timeDash.stop();
	}
}

void KeyController::stopDash()
{
	if (timeDash.isRunning()) {
		isDash = false;
		timeDash.stop();
		isStand = true;
	}
}

void KeyController::updateDash()
{
	if (timeDash.isRunning())
	{
		timeDash.update();
		state = dash;
		stateShoot = dash_shoot;
	}
	else
	{
		if (isDash) 
		{
			timeDash.stop();
			isDash = false;
		}
	}
		
}
#pragma endregion

#pragma region Run Stand
void KeyController::addKeyArrow(bool isLeft)
{
	pressArrow += 1;
	if (pressArrow == 2)
	{
		left = true;
		right = true;
		isRun = false;
		isHoldLeft = isHoldRight = false;
	}
	else 
	{
		if (isLeft != toLeft) stopDash(); //cancel dash
		isLeft ? left = true : right = true;
		toLeft = isLeft;
		isRun = true;
	}
}

void KeyController::removeKeyArrow(bool isLeft)
{
	pressArrow -= 1;
	if (pressArrow == 1)
	{
		isLeft ? left = false : right = false;
		toLeft = !isLeft;
		isRun = true;
	}
	else 
	{
		left = false;
		right = false;
		isRun = false;
		isHoldLeft = isHoldRight = false;
	}
	
}

void KeyController::stopRun()
{
	if (isRun)
	{
		left = false;
		right = false;
		isRun = false;
	}
}

void KeyController::updateRun()
{
	if (!(isDash || onAir))
	{
		if (isRun)
			state = run,
			stateShoot = run_shoot;
		else 
			state = stand,
			stateShoot = shoot;
	}
}
#pragma endregion


UINT KeyController::getState(bool& isLeft)
{
	isLeft = toLeft;
	
	return isShot ? stateShoot : state;
}
