#include "KeyController.h"
#include "Debugs.h"
#include "Elevator.h"

#pragma region Check Key
void KeyController::setHurt(bool isTrue)
{
	isHurt = isTrue;
	if (isTrue)
	{
		stopDash();
		stopFallOrSlide();
		isStand = true;
	}
}
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
	if (isHurt)
	{
		state = shock;
		stateShoot = shock;
		main->speed.vy = 0;
		main->speed.vx = 0;
		return;
	}

	if (wall)
	{
		int distanceLeft = wall->x - (main->x + width);
		int distanceRight = main->x - (wall->x + wall->width);

		if (distanceLeft > 3 || distanceRight > 3) //5 is safe collision
			isWall = false,
			wall = NULL;
		else
		{
			
			int distanceTop = wall->y - (main->y + this->height);

			int distanceBottom = main->y - (wall->y + wall->height);
			if (distanceTop >4)
				isWall = false,
				wall = NULL;
		}
	}

	if (this->floor && !onAir)
	{
		int distanceLeft = floor->x - (main->x + width);
		int distanceRight = main->x - (floor->x + floor->width);
		if (distanceLeft > 5 || distanceRight > 5)
			onAir = true,
			statusJump = StatusJump::Fall,
			floor = NULL;
	}

	_update();
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

KeyController::KeyController(GameObject * megaman, MegamanEffectFactory* effect, MegamanWeapon *weapon, bool left)
{
	this->effect = effect;
	this->weapon = weapon;
	main = megaman;
	toLeft = left;
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
			state = MegaManAnimation::jump;
			stateShoot = jump_shoot;
			width = Jump_Shoot_Width;
			height = Jump_Shoot_Height;
			main->speed.vy = -0.15f; 
			break;
		case StatusJump::Kick:
			state = MegaManAnimation::cling;
			stateShoot = cling_shoot;
			width = Jump_Shoot_Width;
			height = Jump_Shoot_Height;
			main->speed.vy = -0.185f;
			break;

		case StatusJump::Fall:
			state = MegaManAnimation::fall;
			stateShoot = fall_shoot;
			width = Fall_Shoot_Width;
			height = Fall_Shoot_Height;
			break;

		case StatusJump::Slide:
			state = MegaManAnimation::slide;
			stateShoot = slide_shoot;
			main->speed.vy -= 0.0001f * main->dt;
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
		main->speed.vx = toLeft ? -0.15f : 0.15f;
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
	levelShoot = 0;
}

void KeyController::removeKeyZ()
{
	pressZ = false;
	isShot = true;
	if (isHurt)
	{
		timePressZ.stop();
		timeShoot.stop();
		return;
	}

	timePressZ.stop();
	timeShoot.start();
	effect->stopShoot();

	bool left = this->statusJump == StatusJump::Slide ? !toLeft : toLeft;

	if (left)
		weapon->createWeapon(main->x, main->y + height / 2 - 2, levelShoot, true);
	else
		weapon->createWeapon(main->x + width, main->y + height / 2 - 2, levelShoot, false);
}

void KeyController::stopShoot() 
{
	isShot = false;
	timePressZ.stop();
	timeShoot.stop();
	effect->stopShoot();
}

void KeyController::updateShoot()
{
	if (pressZ)
	{
		timePressZ.update();
		if (timePressZ.getTime() > 500 && levelShoot == 0)
			effect->createShoot(++levelShoot);
		else
			if (timePressZ.getTime() > 2500 && levelShoot == 1)
				effect->createShoot(++levelShoot);
	}
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
		if (isWall && timeKick.isStop())
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
		if (timeKick.isRunning())
		{
			timeKick.update();
			main->x += toLeft ? 1.5 : -1.5;
		}
		else statusJump = Jump;
		timeslideDelay.start();
	}
	else if(onAir)
	{
		if (StatusJump::Jump == statusJump || statusJump == StatusJump::Kick) 
			stopJumpRunning();
		if (statusJump == StatusJump::Slide)
		{
			if (!wall || !isRun || isWallLeft != toLeft)
			{
				statusJump = StatusJump::Fall;
				return;
			}
			timeslideDelay.update();

			if (timeslideDelay.isStop())
			{
				if (toLeft)
					effect->createWallSlide(main->x, main->y + height - 8);
				else
					effect->createWallSlide(main->x + width, main->y + height - 8);
				timeslideDelay.start();
			}
		}
		else
		if (statusJump == StatusJump::Fall && wall && pressArrow == 1 && isWallLeft == toLeft)
		{
			statusJump = StatusJump::Slide;
			return;
		}			
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
	timeKick.start();
	timeJump.start();
	statusJump = StatusJump::Kick;
	if (toLeft)
		effect->createWallKick(main->x , main->y + height - 8);
	else
		effect->createWallKick(main->x + width, main->y + height - 8);
}

#pragma endregion

#pragma region Dash
void KeyController::addKeyC()
{
	if (onAir || isWall) return;//----
	pressC = true;
	isDash = true;
	if (isHurt) return;
	timeDash.start();
	//if (toLeft)
	if (toLeft)
		effect->createDashSmoke(main->x + width, main->y + height - 8),
		effect->createDashSpark(main->x + width + 10, main->y + height - 8, true);
	else
		effect->createDashSmoke(main->x, main->y + height - 8),
		effect->createDashSpark(main->x - width, main->y + height - 8, false);
}

void KeyController::removeKeyC()
{
	pressC = false;
	stopDash();
	effect->stopDashSpark();
}

void KeyController::stopDashRunning()
{
	isDash = false;
	timeDash.stop();
	dashSmokeDelay.stop();
}

void KeyController::stopDash()
{
	if (timeDash.isRunning())
	{
		isDash = false;
		timeDash.stop();
		dashSmokeDelay.stop();
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
		dashSmokeDelay.update();
		if (dashSmokeDelay.isStop())
		{
			if (toLeft)
				effect->createDashSmoke(main->x + width, main->y + height - 8);
			else
				effect->createDashSmoke(main->x, main->y + height - 8);
			dashSmokeDelay.start();
		}
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
#pragma endregion

#pragma region Set
void KeyController::setNearWall(bool isLeft, StaticObject* wall)
{
	isWall = true;
	isWallLeft = isLeft;
	this->wall = wall;
}

void KeyController::setFloor(StaticObject *floor)
{
	this->floor = floor;
}

#pragma endregion

#pragma region get
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

#pragma endregion

