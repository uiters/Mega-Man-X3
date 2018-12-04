#ifndef _ConstEnum_H_
#define _ConstEnum_H_

enum class ObjectType
{
	None,
	Item,
	Enemy,
	Boss,
	Sceme,
	Terrain,
	Other
};

enum class ObjectID {
	Brick,
	Wall,
	Door,

};

enum class ColllisionDirect {
	None,
	Left,
	Top,
	Right,
	Bottom
};


enum TextureID
{
	Megaman = 1,
};

enum WeaponID
{
	bullet_lv1 = 13000,
	bullet_lv2 = 13100,
	bullet_lv3 = 13200,

};

enum MegaManAnimation {
	appear = 10000,
	stand = 10100,
	run = 10200,
	jump = 10300,
	dash = 10400,
	fall = 10500,
	cling = 10600,
	enhance = 10700,
	shock = 10800,

	shoot = 11100,
	run_shoot = 11200,
	jump_shoot = 11300,
	dash_shoot = 11400,
	fall_shoot = 11500,
	cling_shoot = 11600,

};
#endif // !_ConstEnum_H_
