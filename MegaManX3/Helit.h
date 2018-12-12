#ifndef _Helit_H_
#define _Helit_H_
#include "DynamicObject.h"
class Helit :
	public DynamicObject
{
private:
	Helit();
public:
	void loadResources() override;
	Helit(int id, float x, float y, bool toLeft);
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	Helit* clone(int id, int x, int y) override;
	~Helit();
};

#endif // !_Helit_H_