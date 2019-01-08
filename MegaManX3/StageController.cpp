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

StageController::~StageController()
{

}

void StageController::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
	if (!isReset && main->isRevivaling)
	{
		isReset = true;
		cameraGlobal->resetState();
		auto index = cameraGlobal->getState();
		stage->setPointRevival();
		index = index < 4 ? 3 : index;
		for (index; index < 11; ++index)
		{
			stages[index]->reset();
		}
		main->speed.vx = 0;
		main->speed.vy = 0.01f * dt;
		//auto obj = staticObjects[0][ID_BLOCK_BACK_WARD];
		//if (obj)
		//	staticObjects[0].erase(ID_BLOCK_BACK_WARD);
	}

	auto index = cameraGlobal->getState();
	stage = stages[index];
	stagePre = stages[index - 1];

	if (isReset && !main->isRevivaling)
	{
		isReset = false;
	}

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
	if (!main->isRevivaling)
	{
		auto block = camera->getBlock();
		if (block)
			objs[ID_BLOCK_BACK_WARD] = block;
	}
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
