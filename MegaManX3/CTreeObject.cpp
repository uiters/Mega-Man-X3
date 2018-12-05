#include "CTreeObject.h"


CTreeObject::CTreeObject(LPObject object, CRectangle& region)
{
	this->object = object;
	this->region = region;
	//delete region;
}

CTreeObject::~CTreeObject()
{
}
