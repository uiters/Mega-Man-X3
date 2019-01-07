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
	TChargedCollision = 4,
	TShurikein = 5,

	THeadGun = 16,
	TBlastHornet = 999,

	TDashSmoke = 2000,
	TDashSpark = 2001,
	TKick = 2002,
	TSlide = 2003,
	TCharged1 = 2004,
	TCharged2 = 2005,
	THelit = 2006,
	THPBar = 2222,
	TBackground2 = 2223,
	TBackground = 2224,
	TGate = 2225,
};
enum ShurikeinAnimation
{
	manifest = 14000,
	roll = 14100,
	spin = 14200,
	fast_roll = 14300,
	normal = 14400,
	fast_spin = 14500,
	fly = 15000,
	jet = 15100,
	illuminate = 15200,
};
enum WeaponID
{
	bullet_lv1 = 13000,
	bullet_lv2 = 13100,
	bullet_lv3 = 13200,

	bullet_head_gun_state_default = 13250,
	bullet_head_gun_state_2 = 13260,

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
	Charged1_Collision_Animation = 12150, // 2 cells
	Charged2_Collision_Animation = 12155, // 2 cells
	Buster_Collision_Animation = 12160, //3 cells
	//Buster_Collision_Animation = 12170, //3cell

	Hornet_Stand = 90000,
	Hornet_Prepare_Prick = 99000,
	Hornet_Prick = 99900,
	Hornet_Drop_Bee_1 = 99990,
	Hornet_Drop_Bee_1_1 = 99890,
	Hornet_Drop_Bee_1_End = 98790,
	Hornet_Drop_Bee_2_Prepare = 88010,
	Hornet_Drop_Bee_2 = 80010,
	Hornet_Drop_Bee_2_End = 81810,
	Hornet_Prick_End = 80810,
	Hornet_Die = 99999,
	Hornet_Explosion = 999969,
	Hornet_Bee_Type_1 = 96000,
	Hornet_Bee_Type_2 = 96002,
	Hornet_Bee_Die_1 = 96960,
	Hornet_Bee_Die_2 = 96962,
	Hornet_Bee_Explosion = 969690,
	Hornet_Wing = 969696,
	Hornet_Aim = 800000,
	Hornet_Aimming = 811000,

	Hornet_Show = 811100,
	
	HpHead = 22000,
	HpTailMain = 22222,
	HpTailBoss = 22220,
	HpBody = 222200,
	HpEntry = 22002,
	BackgroundBoss = 22019,
	BackgroundAni = 20210,
	Background2Ani = 21210,
	Gate1Open = 30000,
	Gate1Close = 30100,
	Gate2Open = 30200,
	Gate2Close = 30300,
	Gate1Lock = 30400,
	Gate2Lock = 30401,
	GateLock = 33000,
	GateOpen = 33001,
	GateClose = 33002,
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
