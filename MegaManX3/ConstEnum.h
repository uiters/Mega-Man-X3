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

enum WeaponID {

};

#endif // !_ConstEnum_H_
