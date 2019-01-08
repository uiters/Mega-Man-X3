#include "Stage.h"

void Stage::updateMain(DWORD dt)
{
	main->dx = main->speed.vx * dt;
	main->x += main->dx;
}

Stage::Stage()
{
	main = dynamic_cast<MegamanX*>(mainGlobal);
}


Stage::~Stage()
{
}
