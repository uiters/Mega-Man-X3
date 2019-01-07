#include "StageController.h"

StageController::StageController()
{
	camera = cameraGlobal;
	main = dynamic_cast<MegamanX*>(mainGlobal);
	stages[1] = new StageElevator();
	stages[2] = stages[1];
	stages[3] = stages[2];
	stages[4] = new Stage4();
	stages[5] = new StageMiniBoss1();
	stages[6] = new StageMiniBoss2();
	stages[7] = new StageByte();
	stages[8] = new Stage8();
	stages[9] = new StageWaitBoss();
	stages[10] = new StageBoss();
}

StageController * StageController::_instance = null;

StageController * StageController::getInstance()
{
	if (!_instance) _instance = new StageController();
	return _instance;
}


void StageController::getEnemies(DWORD dt)
{

}


StageController::~StageController()
{

}

void StageController::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	auto index = cameraGlobal->getState();
	stage = stages[index];
	stagePre = stages[index  - 1];
	if (stage)
	{
		stage->update(dt, staticObjects);
	}
}

void StageController::render(DWORD dt, D3DCOLOR colorBrush)
{
	if (stage)
		stage->render(dt);
	if (cameraGlobal->isSwitchState() && stagePre)
		stagePre->render(dt);
}

void StageController::getStaticObjects(unordered_map<int, GameObject*>& objs)
{
	auto block = camera->getBlock();
	if (block)
		objs[ID_BLOCK_BACK_WARD] = block;
	if (stage)
	{
		stage->getStaticObjects(&objs);
	}
}

void StageController::getDynamicObjects(unordered_map<int, GameObject*>& objs)
{
	if (stage)
	{
		stage->getDynamicObjects(&objs);
	}
}

HPBar * StageController::getHPBar()
{
	if (stage)
	{
		auto stageBoss = dynamic_cast<StageBoss*>(stage);
		if (stageBoss)
			return stageBoss->getHPBar();
	}
	return null;
}
