#pragma once
#include "Stage.h"
#include "Elevator.h"
class StageElevetor :
	public Stage
{
private:
	Camera* camera;
	Elevator* elevator;
	bool isResetLocation = false;
	int wait = 0;
	float initX;
	float initY;
public:
	StageElevetor();
	~StageElevetor();


public:
	void getStaticObjects(unordered_map<int, GameObject*> *saticObjects);
	void getDynamicObjects(unordered_map<int, GameObject*> *dynamicObjects);

public:
	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));
	void reset();
};

