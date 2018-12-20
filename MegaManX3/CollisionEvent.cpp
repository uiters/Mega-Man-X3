#include "CollisionEvent.h"

Collision::Collision(){}
Collision* Collision::_instance;
LPCollisionEvent Collision::sweptAABBEx(DWORD dt, LPObject objectMove, LPObject objectCollision)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	objectCollision->getBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	//float svx, svy;
	//svx = objectCollision->speed.vx;
	//svy = objectCollision->speed.vy;

	//float sdx = svx * dt;
	//float sdy = svy * dt;

	float dx = objectMove->dx -objectCollision->dx;
	float dy = objectMove->dy - objectCollision->dy;

	objectMove->getBoundingBox(ml, mt, mr, mb);

	sweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CollisionEvent * e = new CollisionEvent(t, nx, ny, objectCollision);
	return e;
}

Collision * Collision::getInstance()
{
	if (_instance == NULL)
		_instance = new Collision();
	return _instance;
}

void  Collision::findCollisions(DWORD dt, LPObject objectMove, const unordered_map<int, GameObject*>& objects, vector<LPCollisionEvent> &coEvents)
{
	coEvents.clear();
	for (auto keyValue : objects)
	{
		LPCollisionEvent e = sweptAABBEx(dt, objectMove, keyValue.second);
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
	//debugOut(L"%i\n", coEvents.size());
}

void Collision::findCollisions(DWORD dt, LPObject objectMove, vector<GameObject*>* objects, vector<LPCollisionEvent> &coEvents)
{
	coEvents.clear();
	for (auto item : *objects)
	{
		LPCollisionEvent e = sweptAABBEx(dt, objectMove, item);
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else delete e;
	}
	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void Collision::filterCollision(vector<LPCollisionEvent>& coEvents, vector<LPCollisionEvent>& coEventsResult, float & min_tx, float & min_ty, float & nx, float & ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;

	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); ++i)
	{
		CollisionEvent* c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void Collision::slide(float& vx, float& vy, float nx, float ny, float t)
{
	float dotprod = (vx * ny + vy * nx) * t;
	vx = ny * dotprod;
	vy = nx * dotprod;
}

ColllisionDirect Collision::getCollisionDirect(float normalx, float normaly)
{
	if (normalx == 0 && normaly == 1)
	{
		return ColllisionDirect::Bottom;
	}
	if (normalx == 0 && normaly == -1)
	{
		return ColllisionDirect::Top;
	}
	if (normalx == 1 && normaly == 0)
	{
		return ColllisionDirect::Left;
	}
	if (normalx == -1 && normaly == 0)
	{
		return ColllisionDirect::Right;
	}
	return ColllisionDirect::None;
}

void Collision::sweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float &t, float &nx, float &ny)
{

	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999.f;
		tx_exit = 99999999999.f;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999.f;
		ty_exit = 99999999999.f;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}