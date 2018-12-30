#include "SolskjærController.h"



SolskjærController::SolskjærController()
{
	barrier = new BarrierSystem();
	solskjær = new Solskjær();
	carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);

	isOnlyOne_1 = isOnlyOne_2 = true;
	counter = 0;
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
			generateSolskjær(dt);
		}
	}
	if (solskjær->isDie) barrier->isHidden = true;
}

void SolskjærController::render(DWORD dt)
{
	if (!barrier->isHidden) {
		solskjær->render(dt);
		barrier->render(dt);
		carryArmFirst->render(dt);
		if (carryArmSecond != NULL) carryArmSecond->render(dt);
	}
	else
	{
		barrier->render(dt);
	}
}

void SolskjærController::generateCarryArm(DWORD dt)
{
	if (carryArmFirst->isDie) {
		if (isOnlyOne_1) {
			carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);
			isOnlyOne_1 = false;
		}
		carryArmFirst->update(dt);

		return;
	}
	
	if (!carryArmFirst->isDie && carryArmFirst->isComplete) {
		if (isOnlyOne_2) {
			carryArmSecond = new CarryArm(barrier->initX + 36, barrier->initY - 20, true);
			isOnlyOne_2 = false;
		}
		carryArmSecond->update(dt);

		return;
	}

	carryArmFirst->update(dt);
	if (carryArmSecond != NULL) carryArmSecond->update(dt);
}

void SolskjærController::generateSolskjær(DWORD dt)
{
	if (carryArmSecond != NULL && carryArmSecond->isComplete) {
		counter++;
		if (counter >= 800) {
			solskjær = new Solskjær();
			counter = 0;
		}
		solskjær->update(dt);

		return;
	}
}
