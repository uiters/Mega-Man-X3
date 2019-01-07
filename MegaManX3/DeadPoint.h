#ifndef _DeadPoint_H_
#define _DeadPoint_H_



#include "StaticObject.h"
class DeadPoint :
	public StaticObject
{
public:
	DeadPoint(UINT id, int x, int y, int width, int height);
	~DeadPoint();
};

#endif // !_DeadPoint_H_