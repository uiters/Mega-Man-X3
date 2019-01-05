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
		currentStatic[0][ID_ELEVATOR] = elevator;
	}
	else isEnableElevator = false;
}

void StageController::getEnemies(DWORD dt)
{

}

void StageController::updateElevator(DWORD dt)
{
	if (!isEnableElevator) return;
	elevator->update(dt);

	auto elevatorBox = elevator->getBoundBox();
	


	if (isResetLocation && elevator->y < 684.f)
		elevator->stopRun(),
		elevator->y = 684.f,
		isResetLocation = false;

	if (!elevatorBox.intersectsWith(camera->viewport))//in camera
	{
		if (isResetLocation || elevator->y > camera->viewport.y) return;
		if (wait < 300)
		{
			++wait;
			return;
		}
		else wait = 0;

		elevator->y = ((camera->viewport.y / 256) + 1) * 256 + 32;//Now, sure in bottom camera.
		elevator->run();

		if (camera->viewport.y < 448)
			isResetLocation = false;
		else
			isResetLocation = true;
	}
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
