#ifndef _CTreeObject_H_
#define _CTreeObject_H_

#include "ConstGlobals.h"
template <typename T>
class CTreeObject
{
public:
	CRectangle* region;
	T object;
	CTreeObject<T>(T object, CRectangle* region);
	~CTreeObject();
};

#endif // !_CTreeObject_H_
