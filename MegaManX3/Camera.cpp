#include "Camera.h"


void Camera::switchState()
{
	switch (nAnimation)
	{
	case 2:
		if (viewport.x >= 768)
			aniSwitchState = false, viewport.x = 768;
		else viewport.x += 4;
		break;
	case 3:
		if (viewport.y <= 0)
			aniSwitchState = false;
		else viewport.y -= 1;
		break;
	case 4:
		if (viewport.x >= 1024)
			aniSwitchState = false, viewport.x = 1024;
		else viewport.x += 4;
		break;
	case 5:
		if (viewport.x >= 2304)
			aniSwitchState = false, viewport.x = 2304;
		else viewport.x += 4;
		break;
	case 6:
		if (viewport.x >= 2560)
			aniSwitchState = false, viewport.x = 2560;
		else viewport.x += 4;
		break;
	case 7:
		if (viewport.x >= 5632)
			aniSwitchState = false, viewport.x = 5632;
		else viewport.x += 4;
		break;
	case 8:
		if(viewport.x >= 5888)
			aniSwitchState = false, viewport.x = 5888;
		else viewport.x += 4;
		break;
	case 9:
		if (viewport.x >= 7424)
			aniSwitchState = false, viewport.x = 7424;
		else viewport.x += 4;
		break;
	case 10:
		if (viewport.x >= 7680)
			aniSwitchState = false, viewport.x = 7680;
		else viewport.x += 4;
		break;
	default:
		break;
	}
}

//start
void Camera::state1(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 736, 512, 31, 256);
		nextAnimation();
		lockLeft = true;
		lockTop = true;
		minValue = 0;
		maxValue = 512;
		state = &Camera::state2;
	}
	else
		if (cameraX <= minValue)
		{
			if (lockLeft) return;

			lockLeft = true;
			viewport.x = minValue;
		}
		else if (lockLeft)
			lockLeft = false;
}

//elevator
void Camera::state2(int cameraX, int cameraY)
{
	if (cameraY < minValue + 32)
	{
		delete blockBackward;
		blockBackward = null;
		nextAnimation();
		lockTop = true;
		minValue = 768;
		maxValue = 896;
		state = &Camera::state3;
	}else
		if (cameraY >= maxValue - 64)
		{
			if (viewport.y + 5 < maxValue)
				viewport.y += 5;
			else viewport.y = maxValue;
			if (lockTop) return;
			lockTop = true;
			//viewport.y = maxValue;
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

//top elevator
void Camera::state3(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 992, 0, 32, 256);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 1024;
		maxValue = 2172;
		state = &Camera::state4;
		return;
	}
	if (cameraX <= minValue)
	{
		if (lockLeft) return;

		lockLeft = true;
		viewport.x = minValue;
	}
	else if (lockLeft)
		lockLeft = false;
}

//run to mini boss 1
void Camera::state4(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 2297, 895, 22, 52);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 2432;
		maxValue = 2432;
		state = &Camera::state5;
		return;
	}
	if (cameraX < minValue)
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = minValue;
		}
		return;
	}
	if (cameraX < 1536 && cameraY > 128)
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = 1536;
		}
	}
	else if (lockLeft) lockLeft = false;

	if (cameraY <= 64 || cameraY >= 768)
	{
		if (lockTop) return;

		lockTop = true;
		viewport.y = cameraY < 64 ? 0 : 768;
	}
	else 
		if (lockTop)
		{
			if (cameraY > 64 && viewport.y - cameraY < 0)
				viewport.y += 10;
			else
				lockTop = false;
		}
}

//mini boss 1
void Camera::state5(int cameraX, int cameraY)
{
	if (cameraX > maxValue) //next
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 2546, 895, 22, 52);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 2560;
		maxValue = 5536;
		state = &Camera::state6;
		return;
	}
	//if (viewport.y < 768) viewport.y = 768;
}

//mini bosss 2
void Camera::state6(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 5632, 895, 17, 61);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 5632;
		maxValue = 5760;
		state = &Camera::state7;
		return;
	}
	if (cameraX <= minValue)
	{
		if (!lockLeft) 
		{
			lockLeft = true;
			viewport.x = minValue;
		}
	}
	else if (lockLeft)
		lockLeft = false;

	if (cameraY >= 672)
	{
		if(viewport.y + 5 < 768)
			viewport.y += 5;
		else viewport.y = 768;

		if (lockTop)
			return;
		lockTop = true;
	}
	else if (lockTop)
	{
		if (cameraY < 672 && viewport.y - cameraY > 0)
			viewport.y -= 5;
		else
		lockTop = false;
	}
}

//bit or byte
void Camera::state7(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 5898, 895, 23, 61);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 5888;
		maxValue = 7296;
		state = &Camera::state8;
		return;
	}
}

//run to wait boss
void Camera::state8(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 7392, 1663, 62, 66);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 7296;
		maxValue = 7552;
		state = &Camera::state9;
		return;
	}
	if ((cameraX <= minValue) || (cameraX < 6144 && cameraY < 1472))
	{
		if (!lockLeft)
		{
			lockLeft = true;
			viewport.x = minValue;
		}
	}
	else if (lockLeft)
		lockLeft = false;

	if (cameraY <= 800)
	{
		if(viewport.y <= 768)
			viewport.y += 4;

		if (viewport.y >= 768)
			viewport.y -= 4;
		if (!lockTop)
		{
			lockTop = true;
		}
		return;
	}

	if(cameraX > minValue && cameraY > 1408)
	{
		viewport.y = 1536;
		if (!lockTop)
		{
			lockTop = true;
		}
		return;
	}

	if(cameraX <= minValue && cameraY >= 1472)
	{
		if (viewport.y + 4 <= 1536)
			viewport.y += 4;
		else viewport.y = 1536;

		if (!lockTop)
		{
			lockTop = true;
		}
	}
	else if (lockTop)
	{
		if (cameraY < 1472 && viewport.y - cameraY > 0)
			viewport.y -= 5;
		else
			lockTop = false;
	}
}

// wait boss
void Camera::state9(int cameraX, int cameraY)
{
	if (cameraX > maxValue)
	{
		delete blockBackward;
		blockBackward = new Brick(ID_BLOCK_BACK_WARD, 7393, 1662, 16, 80);
		nextAnimation();
		lockTop = true;
		lockLeft = true;
		minValue = 7424;
		maxValue = 7552;
		state = &Camera::state10;
		return;
	}
}

// boss
void Camera::state10(int cameraX, int cameraY)
{
	//viewport.x = 7680;
}

Camera::Camera(int x, int y, int width, int height) : viewport(x, y, width, height)
{
	viewport.x = (x / 256) * 256;
	viewport.y = (y / 256) * 256;
	//1
	nAnimation = 1;
	state = &Camera::state1;
	minValue = 0;
	maxValue = 650;
	lockTop = true;
	lockLeft = true;

	//2
	//nAnimation = 2;
	//aniSwitchState = true;
	//state = &Camera::state2;
	//lockTop = true;
	//lockLeft = true;
	//minValue = 0;
	//maxValue = 512;
	
	//shuriken
	//maxValue = 2432;
	//minValue = 2432;
	//lockTop = true;
	//lockLeft = true;
	
	//nAnimation = 10;
	//lockTop = true;
	//lockLeft = true;
	//minValue = 7424;
	//maxValue = 7552;
	//state = &Camera::state10;

	//nAnimation = 5;
	//switch (nAnimation)
	//{
	//case 1:
	//	//viewport.x = 0;
	//	//viewport.y = 2 * 256;
	//	state = &Camera::state1;
	//	minValue = 0;
	//	maxValue = 650;
	//	break;
	//case 2:
	//	lockLeft = true;
	//	lockTop = true;
	//	minValue = 0;
	//	maxValue = 512;
	//	state = &Camera::state2;
	//	break;
	//case 3:
	//	lockTop = true;
	//	minValue = 768;
	//	maxValue = 832;
	//	state = &Camera::state3;
	//	break;
	//case 4:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 1024;
	//	maxValue = 2172;
	//	state = &Camera::state4;
	//	break;
	//case 5:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 2432;
	//	maxValue = 2432;
	//	state = &Camera::state5;
	//	break;
	//case 6:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 2560;
	//	maxValue = 5536;
	//	state = &Camera::state6;
	//	break;
	//case 7:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 5632;
	//	maxValue = 5504;
	//	state = &Camera::state7;
	//	break;
	//case 8:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 5888;
	//	maxValue = 7296;
	//	state = &Camera::state8;
	//	break;
	//case 9:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 7296;
	//	maxValue = 7552;
	//	state = &Camera::state9;
	//	break;
	//case 10:
	//	lockTop = true;
	//	lockLeft = true;
	//	minValue = 7424;
	//	maxValue = 7552;
	//	state = &Camera::state10;
	//	break;
	//default:
	//	break;
	//}


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

	(this->*state)(cameraX, cameraY);

	if (!lockLeft) //don't lock camera x
		viewport.x = cameraX;

	if(!lockTop) //don't lock camera y
		viewport.y = cameraY;
}

void Camera::nextAnimation()
{
	nAnimation += 1;
	aniSwitchState = true;
}

const Point Camera::transform(const int& x, const int& y) const
{
	return { x - viewport.x, y - viewport.y };
}