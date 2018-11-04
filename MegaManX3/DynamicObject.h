#ifndef _DynamicObject_H_
#define _DynamicObject_H_
#include "GameObject.h"

class DynamicObject
	:public GameObject
{
protected:
	bool _death;
	vector<int> _damage;

	int _hp; //for reset
	int _levelDamage;
	int _max;

	void addDamage(int damage);

public:
	int hp;
	bool canMove;
	bool canControl;

public:
	void setLevelDamage(int level);
	int getDamage();
	int getMaxLevelDamage();

	void setCanDamage(bool canDamage);
	bool isDeath();

public:
	virtual void receiveDamage(int damage);
	virtual void reset();
};

#endif // !_DynamicObject_H_
