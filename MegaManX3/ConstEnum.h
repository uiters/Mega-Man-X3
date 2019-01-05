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
	TMap = -1,
	TDeath = 0,
	Megaman = 1,
	TElevator = 2,
	TExplosion = 3,
	TChargedExplosion = 4,
	TShurikein = 5,

	TDashSmoke = 2000,
	TDashSpark = 2001,
	TKick = 2002,
	TSlide = 2003,
	TCharged1 = 2004,
	TCharged2 = 2005,
	THelit = 2006,

};
enum ShurikeinAnimation
{
	manifest = 14000,
	roll = 14100,
	spin = 14200,
	fast_roll = 14300,
	normal = 14400,
	fast_spin = 14500,
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
	Charged_Level1 = 12050,
	Charged_Level2 = 12070,
	preDie = 1700,
	die = 1800,

	HelitBody1 = 12100,
	HelitBody2 = 12101,
	HelitAnimation = 12110, //4 cells
	HelitDie = 12120, // 3 cells
	HelitBulletAnimation = 12125, // 1cells
	HelitBulletSmoke = 12130, // 6cells,
	ExplosionAnimation = 12140, //7 cells
	Charged1_Explosion_Animation = 12150, // 2 cells
	Charged2_Explosion_Animation = 12155, // 2 cells
	Buster_Explosion_Animation = 12160, //3 cells
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
enum Sounds {
	sound_bul_lv1 = 21,
	sound_bul_lv2 = 22,
	sound_bul_lv3 = 23,
	sound_charge_lv1 = 24,
	sound_charge_lv2 = 25,
	sound_MX_shock = 26,
	sound_MX_revival = 27,
	sound_MX_dash = 28,
	sound_MX_jump = 29,
	sound_MX_heal = 30,
	sound_MX_die = 31,
	sound_explosion = 33,
	sound_theme = 34,
};
#endif // !_ConstEnum_H_
