#pragma once
#include "DynamicObject.h"
#include "HPBar.h"
#include <time.h>
#include <stdlib.h>
#include "Bee.h"
#include "HornetPoint.h"
#include "HornetExplosion.h"
class BlastHornet :
	public DynamicObject
{
private:
	void loadResources() override;

private:
	bool isDone = false;
	bool stop = false;
	bool lockDirection = false;
	bool isFirst = true;
	int checkX = 1;
	int checkY = -1;
	int width, height;
	int round = 0;
	int maxRound = 0;
	int maxBee = 2;
	int bees = 0;
	int color = 255;
	void(BlastHornet::*mech) ();
	void(BlastHornet::*mechBerk) ();

	HPBar* hpbar;
	unordered_map<int, GameObject*>* currentStatic;
	CTime timeDropBee = CTime(2000);
	CTime timeDropAim = CTime(3000);

	HornetPoint* hornetPoint;
	CTime timeDelayExplosion = (300);
	CTime delay = (100);
	bool isCollisionStatic = false;
	HornetExplosion* effect;
public:
	HornetPoint * getHoretPoint();
	BlastHornet();
	~BlastHornet();

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;
	void reset() override;
private:
	void setState(UINT state);
	bool collisionStatic();
	void flyArround();
	
	void fly();
	

	void start();
	void addHP();
	void mech1();//prick
	
	void prickPrepare();
	void aimPrick();
	void prick();
	void prickEnd();

	void mech2();
	void dropBeePrepare();
	void createBee();
	void dropBee();
	void dropBeeEnd();

	void mech3();
	void setDirection();

	void berserk();
	void berserkDropBeePrepare();
	void berserkDropBee();
	void berserkDropBeeEnd();

	void receiveDamage(float damage); 
private:
	void updateWeapon(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0) override;
	
};

