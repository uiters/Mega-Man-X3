#ifndef _CollisionEvent_H_
#define _CollisionEvent_H_

#include "GameObject.h"
#include "SweptAABB.h"

class GameObject;
typedef GameObject * Object;

struct CollisionEvent;
typedef CollisionEvent * LPCollisionEvent;

struct CollisionEvent
{
	Object obj;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, Object obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCollisionEvent &a, LPCollisionEvent &b)
	{
		return a->t < b->t;
	}
};






#endif // !_CollisionEvent_
