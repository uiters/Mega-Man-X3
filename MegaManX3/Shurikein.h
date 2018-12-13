#pragma once
#include "DynamicObject.h"
class Shurikein :
	public DynamicObject
{
public:
	Shurikein();
	~Shurikein();
	void loadResoures();
	Shurikein* clone(int id, int x, int y);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
};

