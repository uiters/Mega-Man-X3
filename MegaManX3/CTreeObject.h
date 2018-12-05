#ifndef _CTreeObject_H_
#define _CTreeObject_H_

#include "ConstGlobals.h"
class CTreeObject
{
public:
	CRectangle region;
	LPObject object;
	bool isdel = false;
	CTreeObject(LPObject object, CRectangle& region);
	~CTreeObject();
};

#endif // !_CTreeObject_H_
