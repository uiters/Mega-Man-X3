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
	if (onAir) return;
	
	timeDash.stop();
	pressX = true;

	timeJump.start();
	isJump = true;
	isFall = false;
	onAir = true;
	onFloor = false;
	this->width = Jump_Shoot_Width;
	this->height = Jump_Shoot_Height;
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
		this->width = Fall_Shoot_Width;
		this->height = Fall_Shoot_Height;
	}
}

void KeyController::updateJump()
{
	if (isWall)
	{
		if (pressArrow == 1 && (toLeft == left || !toLeft == right)) 
		{
			if (timeJump.isRunning())
				clingWall();
			else
				slideWall();
		}else
			if (timeJump.isRunning())
				clingWall();
			else
			{
				if (isJump)
				{
					isJump = false;
					isFall = true;
					state = fall;
					stateShoot = fall_shoot;
					this->width = Fall_Shoot_Width;
					this->height = Fall_Shoot_Height;
				}
			}

	}
	else 
	{
		if (timeJump.isRunning())
		{
			state = jump; //current jump
			stateShoot = jump_shoot;
			timeJump.update();
			this->width = Jump_Shoot_Width;
			this->height = Jump_Shoot_Height;
		}
		else
			if (isJump)
			{
				isJump = false;
				isFall = true;
				state = fall;
				stateShoot = fall_shoot;
				this->width = Fall_Shoot_Width;
				this->height = Fall_Shoot_Height;
			}
	}

}

void KeyController::stopFall() 
{
	if (isFall)
	{
		timeJump.stop();
		isJump = false;
		isFall = false;
		onAir = false;

		onFloor = true;

		//state = stand;
		//stateShoot = shoot;
		this->width = Stand_Shoot_Width;
		this->height = Stand_Shoot_Height;

	}
}

#pragma endregion

#pragma region Dash
void KeyController::addKeyC()
{
	if (onAir || isWall) return;
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
	if (timeDash.isRunning() && !onAir)
	{
		timeDash.update();
		state = dash;
		stateShoot = dash_shoot;
		this->width = Dash_Shoot_Width;
		this->height = Dash_Shoot_Height;
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
		if (isRun && !isWall)
			state = run,
			stateShoot = run_shoot, 
			this->width = Run_Shoot_Width,
			this->height = Run_Shoot_Height;
		else 
			state = stand,
			stateShoot = shoot,
			this->width = Stand_Shoot_Height,
			this->height = Stand_Shoot_Height;
	}
}

void KeyController::setNearWall(bool isTrue)
{
	isWall = isTrue;
}

#pragma endregion

#pragma region Wall
void KeyController::clingWall()
{
	state = cling;
	stateShoot = cling_shoot;
	this->width = Cling_Shoot_Width;
	this->height = Cling_Shoot_Height;
}
void KeyController::slideWall()
{
	//state = 
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
