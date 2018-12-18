#ifndef _CollisionEvent_H
#define _CollisionEvent_H
#pragma once

#include "GameObject.h"
#include <algorithm>
#include "CTreeObject.h"

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
class Collision {

public:
	
	static Collision* getInstance();
	// find all collision objectMove with another Objects
	// waring !!!
	void findCollisions(DWORD dt, LPObject objectMove, const unordered_map<int, CTreeObject*>& objects, vector<LPCollisionEvent> &coEvents);
	void findCollisions(DWORD dt, LPObject objectMove, vector<GameObject*> *objects, vector<LPCollisionEvent> &coEvents);


	static ColllisionDirect getCollisionDirect(float normalx, float normaly);
	// Filter Collision
	void filterCollision(vector<LPCollisionEvent> &coEvents, vector<LPCollisionEvent> &coEventsResult,
		float &min_tx,
		float &min_ty,
		float &nx,
		float &ny);
	void slide(float& vx, float& vy, float nx, float ny, float t);
	LPCollisionEvent sweptAABBEx(DWORD dt, LPObject objectMove, LPObject objectCollision);
private:
	static Collision* _instance;
	Collision();
	// ex sweptAABB
	


	void sweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float &t, float &nx, float &ny);
};


#endif // !_CollisionEvent_
