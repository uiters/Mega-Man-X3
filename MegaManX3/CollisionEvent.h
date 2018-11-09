#ifndef _CollisionEvent_H
#define _CollisionEvent_H


#include "GameObject.h"
#include <algorithm>

using namespace std;

class GameObject;
typedef GameObject * LPObject;

struct CollisionEvent;
typedef CollisionEvent * LPCollisionEvent;

struct CollisionEvent
{
	LPObject obj;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, LPObject obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCollisionEvent &a, LPCollisionEvent &b)
	{
		return a->t < b->t;
	}
};
void sweptAABB(float ml, float mt, float mr, float mb, float dx, float dy, float sl, float st, float sr, float sb, float &t, float &nx, float &ny);

// ex sweptAABB
LPCollisionEvent sweptAABBEx(DWORD dt, LPObject objectMove, LPObject objectCollision);

// find all collision objectMove with another Objects
// waring !!!
vector<LPCollisionEvent> findCollisions(DWORD dt, LPObject objectMove, vector<LPObject> *Objects);


// Filter Collision
void filterCollision(vector<LPCollisionEvent> &coEvents, vector<LPCollisionEvent> &coEventsResult,
	float &min_tx,
	float &min_ty,
	float &nx,
	float &ny);
ColllisionDirect getCollisionDirect(float normalx, float normaly);







#endif // !_CollisionEvent_
