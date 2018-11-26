#include "MegamanX.h"
#include "Camera.h"


MegamanX::MegamanX()
{
}


MegamanX::~MegamanX()
{
}

void MegamanX::onKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_UP:
		cameraGlobal->viewport.y += 10;
		break;
	case DIK_DOWN:
		cameraGlobal->viewport.y -= 10;
		break;
	case DIK_RIGHT:
		cameraGlobal->viewport.x += 10;
		break;
	case DIK_LEFT:
		cameraGlobal->viewport.x -= 10;
		break;
	default:
		break;
	}
}

void MegamanX::onKeyUp(int keyCode)
{
	
}

void MegamanX::keyState(BYTE *state)
{
	
}
