#pragma once
#include "DynamicObject.h"
#include "HPBar.h"
#include <time.h>
#include <stdlib.h>
class BlastHornet :
	public DynamicObject
{
private:
	void loadResources() override;
	void(BlastHornet::*mech) ();
	bool isDone = false;
	bool stop = false;
	bool lockDirection = false;
	bool isFirst = true;
	HPBar* hpbar;
	int width, height;
	unordered_map<int, GameObject*>* currentStatic;
public:
	BlastHornet();
	~BlastHornet();

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:
	void fly();
	void aimPrick();

	void start();
	void addHP();
	void mech1();//prick
	
	void prickShow();
	void prick();
	void prickEnd();

	void mech2();

	void setDirection();
};

