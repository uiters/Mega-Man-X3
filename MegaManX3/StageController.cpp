#include "StageController.h"



StageController::StageController()
{
	collision = Collision::getInstance();
	camera = cameraGlobal;
	megaman = dynamic_cast<MegamanX*>(mainGlobal);
}

StageController * StageController::_instance = null;

StageController * StageController::getInstance()
{
	if (!_instance) _instance = new StageController();
	return _instance;
}

void StageController::getStaticObject(DWORD dt)
{
	auto block = camera->getBlock();
	if (block)
		currentStatic[0][ID_BLOCK_BACK_WARD] = block;

	if (camera->viewport.x > 576 && camera->getState() < 4)
	{
		isEnableElevator = true;
	}
	else isEnableElevator = false;
}

void StageController::getEnemies(DWORD dt)
{

}

void StageController::updateElevator(DWORD dt)
{
	if (!isEnableElevator) return;

}

void StageController::renderElevator(DWORD dt)
{
	if (!isEnableElevator) return;
	elevator->render(dt);
}

StageController::~StageController()
{

}

void StageController::update(DWORD dt)
{
	getStaticObject(dt);
	getEnemies(dt);
}
