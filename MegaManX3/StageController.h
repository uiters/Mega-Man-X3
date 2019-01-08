#ifndef _StageController_H_
#define _StageController_H_
#include "Camera.h"
#include "MegamanX.h"

#include "StageElevator.h"
#include "Stage4.h"
#include "Stage8.h"
#include "StageBoss.h"
#include "StageByte.h"
#include "StageMiniBoss1.h"
#include "StageMiniBoss2.h"
#include "StageWaitBoss.h"

class StageController
{
private:
	Camera* camera;
	MegamanX* main;
	Stage* stage;
	Stage* stagePre;
	unordered_map<int, Stage*> stages;

	bool* enableUpdateController;
	static StageController* _instance;
	bool isReset = false;
private:
	StageController();
public:
	static StageController* getInstance();
	~StageController();


public:

	void update(DWORD dt, unordered_map<int, GameObject*>* staticObjects);
	void render(DWORD dt, D3DCOLOR colorBrush = WHITE(255));

public:
	void setEnableUpdateController(bool* enable) { this->enableUpdateController = enable; }

public:
	void getStaticObjects(unordered_map<int, GameObject*>& objs);
	void getDynamicObjects(unordered_map<int, GameObject*>& objs);
	HPBar* getHPBar();
	HornetPoint* getHornetPoit();
};

#endif // !_StageController_H_