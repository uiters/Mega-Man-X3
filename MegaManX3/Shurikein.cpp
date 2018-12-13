#include "Shurikein.h"
#include "Animation.h"


Shurikein::Shurikein()
{
}


Shurikein::~Shurikein()
{
}

void Shurikein::loadResoures()
{	
#pragma region manifest
	auto ani = new CAnimation(50);
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
	spritesGlobal->add(manifest + 16, TShurikein, 358, 69, 378, 99);
	spritesGlobal->add(manifest + 17, TShurikein, 387, 69, 407, 89);
	spritesGlobal->add(manifest + 18, TShurikein, 419, 67, 441, 89);
	spritesGlobal->add(manifest + 19, TShurikein, 448, 67, 471, 89);
	spritesGlobal->add(manifest + 20, TShurikein, 58, 112, 82, 136);
	spritesGlobal->add(manifest + 21, TShurikein, 90, 111, 116, 37);
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
	spritesGlobal->add(manifest + 43, TShurikein, 147, 210, 195, 285);
	spritesGlobal->add(manifest + 44, TShurikein, 202, 208, 250, 256);
	spritesGlobal->add(manifest + 45, TShurikein, 259, 210, 305, 256);
	spritesGlobal->add(manifest + 46, TShurikein, 316, 212, 360, 255);
	spritesGlobal->add(manifest + 47, TShurikein, 369, 211, 415, 257);
	spritesGlobal->add(manifest + 48, TShurikein, 429, 209, 475, 255);
	spritesGlobal->add(manifest + 49, TShurikein, 481, 208, 527, 254);
	spritesGlobal->add(manifest + 50, TShurikein, 15, 271, 61, 317);
	spritesGlobal->add(manifest + 51, TShurikein, 69, 217, 113, 315);
	spritesGlobal->add(manifest + 52, TShurikein, 120, 273, 166, 319);
	spritesGlobal->add(manifest + 53, TShurikein, 174, 217, 222, 318);
	spritesGlobal->add(manifest + 54, TShurikein, 228, 271, 276, 319);
	spritesGlobal->add(manifest + 55, TShurikein, 284, 274, 330, 320);
	spritesGlobal->add(manifest + 56, TShurikein, 340, 274, 384, 318);
	spritesGlobal->add(manifest + 57, TShurikein, 399, 274, 443, 318);
	spritesGlobal->add(manifest + 58, TShurikein, 451, 273, 497, 319);
	spritesGlobal->add(manifest + 59, TShurikein, 502, 274, 550, 322);

	ani->add(manifest);
	ani->add(manifest + 1);
	ani->add(manifest + 2);
	ani->add(manifest + 3);
	ani->add(manifest + 4);
	ani->add(manifest + 5);
	ani->add(manifest + 6);
	ani->add(manifest + 7);
	ani->add(manifest + 8);
	ani->add(manifest + 9);
	ani->add(manifest + 10);
	ani->add(manifest + 11);
	ani->add(manifest + 12);
	ani->add(manifest + 13);
	ani->add(manifest + 14);
	ani->add(manifest + 15);
	ani->add(manifest + 16);
	ani->add(manifest + 17);
	ani->add(manifest + 18);
	ani->add(manifest + 19);
	ani->add(manifest + 20);
	ani->add(manifest + 21);
	ani->add(manifest + 22);
	ani->add(manifest + 23);
	ani->add(manifest + 24);
	ani->add(manifest + 25);
	ani->add(manifest + 26);
	ani->add(manifest + 27);
	ani->add(manifest + 28);
	ani->add(manifest + 29);
	ani->add(manifest + 30);
	ani->add(manifest + 31);
	ani->add(manifest + 32);
	ani->add(manifest + 33);
	ani->add(manifest + 34);
	ani->add(manifest + 35);
	ani->add(manifest + 36);
	ani->add(manifest + 37);
	ani->add(manifest + 38);
	ani->add(manifest + 39);
	ani->add(manifest + 40);
	ani->add(manifest + 41);
	ani->add(manifest + 42);
	ani->add(manifest + 43);
	ani->add(manifest + 44);
	ani->add(manifest + 45);
	ani->add(manifest + 46);
	ani->add(manifest + 47);
	ani->add(manifest + 48);
	ani->add(manifest + 49);
	ani->add(manifest + 50);
	ani->add(manifest + 51);
	ani->add(manifest + 52);
	ani->add(manifest + 53);
	ani->add(manifest + 54);
	ani->add(manifest + 55);
	ani->add(manifest + 56);
	ani->add(manifest + 57);
	ani->add(manifest + 58);
	ani->add(manifest + 59);
	animationsGlobal->add(manifest, ani);
	this->addAnimation(manifest);
#pragma endregion
#pragma region roll
	auto ani = new CAnimation(100);
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
	ani->add(roll);
	ani->add(roll + 1);
	ani->add(roll + 2);
	ani->add(roll + 3);
	ani->add(roll + 4);
	ani->add(roll + 5);
	ani->add(roll + 6);
	ani->add(roll + 7);
	ani->add(roll + 8);
	ani->add(roll + 9);
	animationsGlobal->add(roll, ani);
	this->addAnimation(roll);
#pragma endregion
#pragma region spin
	auto ani = new CAnimation(100);
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
	ani->add(spin);
	ani->add(spin + 1);
	ani->add(spin + 2);
	ani->add(spin + 3);
	ani->add(spin + 4);
	ani->add(spin + 5);
	ani->add(spin + 6);
	ani->add(spin + 7);
	ani->add(spin + 8);
	ani->add(spin + 9);
	ani->add(spin + 10);
	ani->add(spin + 11);
	ani->add(spin + 12);
	ani->add(spin + 13);
	ani->add(spin + 14);
	ani->add(spin + 15);
	animationsGlobal->add(spin, ani);
	this->addAnimation(spin);
#pragma endregion

}

Shurikein * Shurikein::clone(int id, int x, int y)
{
	return nullptr;
}

void Shurikein::getBoundingBox(float & left, float & top, float & right, float & bottom)
{

}
