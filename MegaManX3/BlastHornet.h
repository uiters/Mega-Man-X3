#pragma once
#include "DynamicObject.h"
#include "HPBar.h"
class BlastHornet :
	public DynamicObject
{
private:
	void loadResources() override;
	void(BlastHornet::*mech) ();
	bool isDone = false;
	bool stop = false;
	int time= 0;
	HPBar* hpbar;
	int width, height;
public:
	BlastHornet();
	~BlastHornet();

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects = 0, unordered_map<int, GameObject*>* dynamicObjects = 0) override;
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255)) override;
	void getBoundingBox(float & left, float & top, float & right, float & bottom) override;

private:

	void start();
	void addHP();
	void mech1();//prick
	void mech2();

	void setDirection();
};

