#include "SolskjærController.h"



SolskjærController::SolskjærController()
{
	barrier = new BarrierSystem();
	solskjær = new Solskjær();
	carryArm = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);

	counterCarryArm = 0;
}


SolskjærController::~SolskjærController()
{
}

void SolskjærController::update(DWORD dt)
{
	barrier->update(dt);
	
	if (!barrier->isHidden) {
		if (barrier->y >= 855) {
			generateCarryArm(dt);
		}
	}
}

void SolskjærController::render(DWORD dt)
{
	solskjær->render(dt);
	barrier->render(dt);
	carryArm->render(dt);
	if (tempBoxLeft != NULL) tempBoxLeft->render(dt);
	if (tempBoxRight != NULL) tempBoxRight->render(dt);
}

void SolskjærController::generateCarryArm(DWORD dt)
{
	if (carryArm->isPutBox) {
		if (carryArm->isLeft && carryArm->isPutBox) {
			tempBoxLeft = new Box(carryArm->putBoxX, carryArm->putBoxY);
			tempBoxLeft->isNext = carryArm->isNext;
			tempBoxLeft->isLeft = true;
		}
		else if (!carryArm->isLeft && carryArm->isPutBox)
		{
			tempBoxRight = new Box(carryArm->putBoxX, carryArm->putBoxY);
			tempBoxRight->isNext = carryArm->isLeft;
			tempBoxRight->isLeft = false;
		}
	}

	if (carryArm->isDie) {
		carryArm = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);
		counterCarryArm++;
		if (counterCarryArm >= 500) {
			counterCarryArm = 0;
			carryArm->update(dt);
		}

		return;
	}
	
	if (!carryArm->isDie && carryArm->isComplete) {
		carryArm = new CarryArm(barrier->initX + 36, barrier->initY - 20, true);
		counterCarryArm++;
		if (counterCarryArm >= 500) {
			counterCarryArm = 0;
			carryArm->update(dt);
		}

		return;
	}

	carryArm->update(dt);
	if (tempBoxLeft != NULL) tempBoxLeft->update(dt);
	if (tempBoxRight != NULL) tempBoxRight->update(dt);
}
