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
	TElevator = 2,

	TDashSmoke = 2000,
	TDashSpark = 2001,
	TKick = 2002,
	TSlide = 2003,

};

enum WeaponID
{
	bullet_lv1 = 13000,
	bullet_lv2 = 13100,
	bullet_lv3 = 13200,

};
enum Animation {
	Elevator1 = 12000,
	Elevator2 = 12001,
	Elevator3 = 12002,

	DashSmokeAnimation = 12003, // 12 cells
	DashSparkAnimation = 12025, // 10 cells
	SlideAnimation = 12036, // 6 cells
	KickAnimation = 12045,// 1 cell

};


enum MegaManAnimation {
	appear = 10000,
	stand = 10100,
	run = 10200,
	jump = 10300,
	dash = 10400,
	fall = 10500,
	cling = 10600,
	slide = 10700,
	enhance = 10800,
	shock = 10900,

	shoot = 11100,
	run_shoot = 11200,
	jump_shoot = 11300,
	dash_shoot = 11400,
	fall_shoot = 11500,
	cling_shoot = 11600,
	slide_shoot = 11700,

};
#endif // !_ConstEnum_H_
