#include "Camera.h"


void Camera::switchState()
{
	switch (state)
	{
	case 2:
		if (viewport.x >= 768)
			aniSwitchState = false;
		else viewport.x += 4;

		break;
	case 3:
		if (viewport.y <= 0)
			aniSwitchState = false;
		else viewport.y -= 1;
		break;
	case 4:
		if (viewport.x >= 1024)
			aniSwitchState = false;
		else viewport.x += 4;
	default:
		break;
	}
}

void Camera::state1(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		nextState();
		lockLeft = true;
		lockTop = true;
		aniSwitchState = true;
		minValue = 0;
		maxValue = 512;
	}
	else
		if (cameraX < minValue)
		{
			if (lockLeft) return;

			lockLeft = true;
			viewport.x = minValue;
		}
		else if (lockLeft)
			lockLeft = false;
}

void Camera::state2(int cameraX, int cameraY)
{
	if (cameraY < minValue + 64)
	{
		nextState();
		lockTop = true;
		minValue = 768;
		maxValue = 832;
		aniSwitchState = true;
	}else
		if (cameraY > maxValue - 64)
		{
			if (lockTop) return;
			lockTop = true;
			viewport.y = maxValue;
		}
		else 
			if (lockTop)
			{
				if (cameraY - viewport.y < 0)
					viewport.y -= 4;
				else
					lockTop = false;
			}
}

void Camera::state3(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		nextState();
		lockTop = true;
		minValue = 768;
		maxValue = 896;
		aniSwitchState = true;
	}
		if (cameraX < minValue)
		{
			if (lockLeft) return;

			lockLeft = true;
			viewport.x = minValue;
		}
		else if (lockLeft)
			lockLeft = false;
}

void Camera::state4(int cameraX, int cameraY)
{
}

void Camera::state5(int cameraX, int cameraY)
{
}

void Camera::state6(int cameraX, int cameraY)
{
}

void Camera::state7(int cameraX, int cameraY)
{
}



Camera::Camera(int x, int y, int width, int height) : viewport(x, y, width, height)
{
	viewport.x = 0;
	viewport.y = 2 * 256;
	state = 1;
	minValue = 0;
	maxValue = 650;

	lockTop = true;
	lockLeft = false;
}

void Camera::update(int x, int y) //center x, center y
{
	if (aniSwitchState)
	{
		switchState();
		return;
	}
	if (!enable) return;

	int cameraX = x - 128;
	int cameraY = y - 128;

	switch (state)
	{
	case 1:
		state1(cameraX, cameraY);
		break;
	case 2:
		state2(cameraX, cameraY);
		break;
	case 3:
		state3(cameraX, cameraY);
		break;
	case 4:
		state4(cameraX, cameraY);
		break;
	case 5:
		state5(cameraX, cameraY);
		break;
	case 6:
		state6(cameraX, cameraY);
		break;
	case 7:
		state7(cameraX, cameraY);
		break;
	default:
		break;
	}

	if (!lockLeft) //don't lock camera x
		viewport.x = cameraX;

	if(!lockTop) //don't lock camera y
		viewport.y = cameraY;
}
void Camera::nextState()
{
	state += 1;
}
void Camera::setSizeWorld(int x, int y, int width, int height)
{
	world.left = x;
	world.right = y;
	world.right = width + x;
	world.bottom = height + y;
}

const Point Camera::transform(const int& x, const int& y) const
{
	return { x - viewport.x, y - viewport.y };
}