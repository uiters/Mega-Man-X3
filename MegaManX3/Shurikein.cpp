#include "Shurikein.h"
#include "Animation.h"
#include "Camera.h"
#include <random>
#include "StaticObject.h"

Shurikein::Shurikein() 
{
	loadResources();
}


Shurikein::~Shurikein()
{
}

void Shurikein::loadResources()
{
	texturesGlobal->add(TShurikein, L"Resource\\Textures\\Shurikein.png", 555, 468, D3DCOLOR_XRGB(64, 48, 72));
#pragma region manifest
	auto ani = new CAnimation(40);
	spritesGlobal->add(manifest, TShurikein, 83, 80, 83, 80);
	spritesGlobal->add(manifest + 1, TShurikein, 88, 79, 90, 81);
	spritesGlobal->add(manifest + 2, TShurikein, 101, 77, 107, 83);
	spritesGlobal->add(manifest + 3, TShurikein, 113, 77, 119, 83);
	spritesGlobal->add(manifest + 4, TShurikein, 124, 76, 132, 84);
	spritesGlobal->add(manifest + 5, TShurikein, 137, 76, 145, 84);
	spritesGlobal->add(manifest + 6, TShurikein, 150, 75, 160, 85);
	spritesGlobal->add(manifest + 7, TShurikein, 165, 75, 175, 85);
	spritesGlobal->add(manifest + 8, TShurikein, 181, 74, 193, 86);
	spritesGlobal->add(manifest + 9, TShurikein, 198, 74, 210, 86);
	spritesGlobal->add(manifest + 10, TShurikein, 217, 73, 231, 87);
	spritesGlobal->add(manifest + 11, TShurikein, 236, 73, 252, 89);
	spritesGlobal->add(manifest + 12, TShurikein, 257, 73, 273, 89);
	spritesGlobal->add(manifest + 13, TShurikein, 280, 72, 296, 88);
	spritesGlobal->add(manifest + 14, TShurikein, 308, 72, 324, 88);
	spritesGlobal->add(manifest + 15, TShurikein, 333, 70, 351, 88);
	spritesGlobal->add(manifest + 16, TShurikein, 358, 69, 378, 89);
	spritesGlobal->add(manifest + 17, TShurikein, 387, 69, 407, 89);
	spritesGlobal->add(manifest + 18, TShurikein, 419, 67, 441, 89);
	spritesGlobal->add(manifest + 19, TShurikein, 448, 67, 471, 89);
	spritesGlobal->add(manifest + 20, TShurikein, 58, 112, 82, 136);
	spritesGlobal->add(manifest + 21, TShurikein, 90, 111, 116, 137);
	spritesGlobal->add(manifest + 22, TShurikein, 122, 111, 148, 137);
	spritesGlobal->add(manifest + 23, TShurikein, 156, 110, 182, 136);
	spritesGlobal->add(manifest + 24, TShurikein, 190, 112, 216, 138);
	spritesGlobal->add(manifest + 25, TShurikein, 226, 111, 254, 139);
	spritesGlobal->add(manifest + 26, TShurikein, 262, 109, 292, 139);
	spritesGlobal->add(manifest + 27, TShurikein, 301, 109, 333, 141);
	spritesGlobal->add(manifest + 28, TShurikein, 341, 109, 373, 141);
	spritesGlobal->add(manifest + 29, TShurikein, 382, 109, 414, 141);
	spritesGlobal->add(manifest + 30, TShurikein, 423, 108, 455, 140);
	spritesGlobal->add(manifest + 31, TShurikein, 464, 107, 498, 141);
	spritesGlobal->add(manifest + 32, TShurikein, 70, 154, 106, 190);
	spritesGlobal->add(manifest + 33, TShurikein, 114, 155, 152, 193);
	spritesGlobal->add(manifest + 34, TShurikein, 160, 158, 198, 196);
	spritesGlobal->add(manifest + 35, TShurikein, 207, 159, 243, 195);
	spritesGlobal->add(manifest + 36, TShurikein, 255, 158, 293, 196);
	spritesGlobal->add(manifest + 37, TShurikein, 305, 158, 345, 198);
	spritesGlobal->add(manifest + 38, TShurikein, 352, 158, 394, 200);
	spritesGlobal->add(manifest + 39, TShurikein, 401, 156, 443, 198);
	spritesGlobal->add(manifest + 40, TShurikein, 452, 157, 494, 199);
	spritesGlobal->add(manifest + 41, TShurikein, 46, 209, 90, 253);
	spritesGlobal->add(manifest + 42, TShurikein, 96, 209, 142, 255);
	spritesGlobal->add(manifest + 43, TShurikein, 147, 210, 195, 258);
	spritesGlobal->add(manifest + 44, TShurikein, 202, 208, 250, 256);
	spritesGlobal->add(manifest + 45, TShurikein, 259, 210, 305, 256);
	spritesGlobal->add(manifest + 46, TShurikein, 316, 212, 360, 255);
	spritesGlobal->add(manifest + 47, TShurikein, 369, 211, 415, 257);
	spritesGlobal->add(manifest + 48, TShurikein, 429, 209, 475, 255);
	spritesGlobal->add(manifest + 49, TShurikein, 481, 208, 527, 254);
	spritesGlobal->add(manifest + 50, TShurikein, 15, 271, 61, 317);
	spritesGlobal->add(manifest + 51, TShurikein, 69, 271, 113, 315);
	spritesGlobal->add(manifest + 52, TShurikein, 120, 273, 166, 319);
	spritesGlobal->add(manifest + 53, TShurikein, 174, 271, 222, 318);
	spritesGlobal->add(manifest + 54, TShurikein, 228, 271, 276, 319);
	spritesGlobal->add(manifest + 55, TShurikein, 284, 274, 330, 320);
	spritesGlobal->add(manifest + 56, TShurikein, 340, 274, 384, 318);
	spritesGlobal->add(manifest + 57, TShurikein, 399, 274, 443, 318);
	spritesGlobal->add(manifest + 58, TShurikein, 451, 273, 497, 319);
	spritesGlobal->add(manifest + 59, TShurikein, 502, 274, 550, 322);

	for (int i = 0; i < 60; i++)
	{
		ani->add(manifest + i);
	}	
	animationsGlobal->add(manifest, ani);
	this->addAnimation(manifest);
#pragma endregion
#pragma region roll
	ani = new CAnimation(30);
	spritesGlobal->add(roll, TShurikein, 0, 356, 45, 402);
	spritesGlobal->add(roll + 1, TShurikein, 52, 355, 98, 401);
	spritesGlobal->add(roll + 2, TShurikein, 106, 357, 150, 401);
	spritesGlobal->add(roll + 3, TShurikein, 162, 355, 208, 401);
	spritesGlobal->add(roll + 4, TShurikein, 222, 355, 270, 403);
	spritesGlobal->add(roll + 5, TShurikein, 280, 354, 328, 402);
	spritesGlobal->add(roll + 6, TShurikein, 335, 354, 383, 402);
	spritesGlobal->add(roll + 7, TShurikein, 390, 353, 436, 399);
	spritesGlobal->add(roll + 8, TShurikein, 446, 355, 490, 399);
	spritesGlobal->add(roll + 9, TShurikein, 498, 353, 544, 399);
	
	for (int i = 0; i < 10; i++)
	{
		ani->add(roll + i);
	}
	animationsGlobal->add(roll, ani);
	this->addAnimation(roll);
#pragma endregion
#pragma region spin
	ani = new CAnimation(40);
	spritesGlobal->add(spin, TShurikein, 2, 412, 48, 460);
	spritesGlobal->add(spin + 1, TShurikein, 54, 412, 98, 460);
	spritesGlobal->add(spin + 2, TShurikein, 103, 412, 145, 460);
	spritesGlobal->add(spin + 3, TShurikein, 150, 412, 190, 460);
	spritesGlobal->add(spin + 4, TShurikein, 197, 412, 233, 460);
	spritesGlobal->add(spin + 5, TShurikein, 238, 412, 272, 460);
	spritesGlobal->add(spin + 6, TShurikein, 278, 412, 310, 460);
	spritesGlobal->add(spin + 7, TShurikein, 314, 412, 344, 460);
	spritesGlobal->add(spin + 8, TShurikein, 348, 412, 376, 460);
	spritesGlobal->add(spin + 9, TShurikein, 381, 412, 407, 460);
	spritesGlobal->add(spin + 10, TShurikein, 412, 412, 434, 460);
	spritesGlobal->add(spin + 11, TShurikein, 441, 412, 459, 460);
	spritesGlobal->add(spin + 12, TShurikein, 465, 412, 476, 460);
	spritesGlobal->add(spin + 13, TShurikein, 487, 413, 495, 461);
	spritesGlobal->add(spin + 14, TShurikein, 504, 412, 511, 460);
	spritesGlobal->add(spin + 15, TShurikein, 518, 412, 524, 460);
	
	for (int i = 0; i < 16; i++)
	{
		ani->add(spin + i);
	}
	for (int i = 14; i > 0; i--)
	{
		ani->add(spin + i);
	}
	animationsGlobal->add(spin, ani);
	this->addAnimation(spin);
#pragma endregion
#pragma region beaten
	ani = new CAnimation(100);
	spritesGlobal->add(beaten, TShurikein, 380, 10, 426, 58);
	ani->add(beaten);
	animationsGlobal->add(beaten, ani);
	this->addAnimation(beaten);
#pragma endregion
#pragma region normal 
	ani = new CAnimation(100);
	spritesGlobal->add(normal, TShurikein, 328, 10, 374, 58);
	ani->add(normal);
	animationsGlobal->add(normal, ani);
	this->addAnimation(normal);
#pragma endregion
}
Shurikein::Shurikein(UINT idTexture, float x, float y, float vx, float vy) :DynamicObject(idTexture, x, y, vx, vy)
{
	loadResources();
	countManifest.start();
	mech = 2;
	inMech = false;
}
Shurikein * Shurikein::clone(int id, int x, int y)
{
	return nullptr;
}

void Shurikein::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects, unordered_map<int, GameObject*>* dynamicObjects)
{
	
	if (!inMech)
	{
		switch (mech)
		{
		case 1:

			break;
		case 2:
			mech2(true);
			inMech = true;
			state = spin;
			break;
		case 3:

			break;
		default:
			break;
		}
	}
	else
	{
		switch (mech)
		{
		case 1:

			break;
		case 2:
			speed.vy += 0.005f;
			break;
		case 3:

			break;
		default:
			break;
		}
	}
	GameObject::update(dt);
	collisionStatic(staticObjects);
}
void Shurikein::collisionStatic(unordered_map<int, GameObject*>* staticObjects)
{
	vector<CollisionEvent*> coEvents;
	vector<CollisionEvent*> coEventsResult;

	collision->findCollisions(dt, this, *staticObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		collision->filterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		if (nx < 0)
		{
			
		}
		else if (nx > 0)
		{
			
		}
		else
		{
			
		}

		if (ny < 0)
		{
			switch (mech)
			{
			case 1:
				speed.vx = 0;
				speed.vy = 0;
				break;
			case 2:
				mech2(true);
				break;
			case 3:
				break;
			default:
				speed.vx = 0;
				speed.vy = 0;
				break;
			}
		}
		else if (ny > 0)
		{
			switch (mech)
			{
			case 1:
				speed.vx = 0;
				speed.vy = 0;
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				speed.vx = 0;
				speed.vy = 0;
				break;
			}
		}
		else
		{

		}	
	}

	UINT size = coEvents.size();
	for (UINT i = 0; i < size; ++i) delete coEvents[i];
}

void Shurikein::render(DWORD dt, D3DCOLOR colorBrush)
{
	auto pos = cameraGlobal->transform(x, y);
	_animations[state]->render(pos.x, pos.y, true, BLACK(255));
	//_animations[state]->render(pos.x - 23, pos.y - 23, false);
}

void Shurikein::getBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;

	right = x + 20;
	top = y + 20;
}

void Shurikein::mech2(bool toLeft)
{
	if (toLeft)
	{
		speed.vx = -0.05f;
		speed.vy = -0.35f;
	}
	else
	{
		speed.vx = 0.05f;
		speed.vy = -0.35f;
	}
}

//room: 2319  2543
//		784	 945
//
//		
//		2344:809						2518:809
//		
//		2344:920	2402:920			2518:920
//
//
//