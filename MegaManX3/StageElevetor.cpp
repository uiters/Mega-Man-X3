#include "StageElevetor.h"



StageElevetor::StageElevetor()
{
	camera = cameraGlobal;
	elevator = new Elevator(0, 847, 690);
	initX = elevator->x;
	initY = elevator->y;
}


StageElevetor::~StageElevetor()
{

}

void StageElevetor::getStaticObjects(unordered_map<int, GameObject*>* saticObjects)
{
	saticObjects[0][ID_ELEVATOR] = elevator;
}

void StageElevetor::getDynamicObjects(unordered_map<int, GameObject*>* dynamicObjects)
{
}

void StageElevetor::update(DWORD dt, unordered_map<int, GameObject*>* staticObjects)
{
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

void StageElevetor::render(DWORD dt, D3DCOLOR colorBrush)
{
	elevator->render(dt, colorBrush);
}

void StageElevetor::reset()
{
	elevator->x = initX;
	elevator->y = initY;
	isResetLocation = false;
	wait = 0;
}
