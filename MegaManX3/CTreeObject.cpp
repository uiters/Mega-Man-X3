#include "CTreeObject.h"

template<class T>
CTreeObject<T>::CTreeObject(T object, CRectangle * region)
{
	this->object = object;
	this->region = region;
}
template<class T>
CTreeObject<T>::~CTreeObject()
{
}
