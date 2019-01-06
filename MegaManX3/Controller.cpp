#include "Controller.h"
#include "CollisionEvent.h"
#include "NotorBanger.h"
#include "StageController.h"

void Controller::filterAndUpdate(DWORD dt, unordered_map<int, GameObject*>& objects)
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		GameObject* obj = (*i).second;
		if (obj->getBoundBox().intersectsWith(*viewPortGlobal))
		{
			obj->setReset();
			currentDynamic[obj->getID()] = obj;
			obj->update(dt, &currentStatic);
		}
		else
		{
			obj->reset();
		}
		++i;
	}
}

void Controller::update(DWORD dt)
{
	currentStatic.clear();
	tilesController->update(viewPortGlobal);
	stageController->update(dt);

	if (!enableUpdate) return;

	
	unordered_map<int, GameObject*> dynamicObjects;// dynamic quatree

	rootStatic->getObjectsIn(viewPortGlobal, currentStatic);// static quadtree
	rootDynamic->getObjectsIn(viewPortGlobal, dynamicObjects);// dynamic quatree

	filterAndUpdate(dt, dynamicObjects);//filter Dynamic Object => current dynamic

	//blastHornet->update(dt, &currentStatic);
	//currentDynamic[-999] = blastHornet;
	currentStatic[-2] = brick1;
	currentStatic[-3] = brick2;
	genjibo->update(dt);
	shurikein->update(dt, &currentStatic);
	currentDynamic[-999] = shurikein;


	main->update(dt, &currentStatic, &currentDynamic);
	stageController->updateElevator(dt);
}

void Controller::render(DWORD dt)
{
	background->render(dt);
	tilesController->render(dt);

	for (auto kv : currentDynamic) 
	{
		kv.second->render(dt);
	}

	weaponEffect->render(dt); //render effect dynamic

	stageController->renderElevator(dt);
	genjibo->render(dt);
	shurikein->render(dt);

	main->render(dt);
	//blastHornet->getHoretPoint()->render(dt);
	hpBarMain->render(true);
	//hpBarBoss->render(true);
}


Controller::Controller(MegamanX* main, QNode * rootStatic, QNode * rootDynamic)
{
	stageController = StageController::getInstance();
	weaponEffect = WeaponEffectController::getIntance();
	stageController->setCurrentDynamic(&currentDynamic);
	stageController->setCurrentStatic(&currentStatic);
	enableUpdate = true;
	stageController->setEnableUpdateController(&enableUpdate);
	background = new BackgroundController();
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->main = main;

	tilesController = new ScenceController();
	blastHornet = new BlastHornet();

	main->state = stand;
	genjibo = new Genjibo(TGenjibo, 2518, 700);
	shurikein = new Shurikein(TShurikein, 2518, 920);
	shurikein->state = manifest;
	shurikein->visible = false;
	genjibo->setShurikein(shurikein);
	hpBarMain = new HPBar(*main->getHp(), 38.0f, 2.0f, true);
	hpBarBoss = new HPBar(*blastHornet->getHp(), 64.0f, 2.0f, false);
	brick1 = new Brick(0, 2297, 895, 22, 52);
	brick2 = new Brick(0, 2546, 895, 22, 52);
}

Controller::~Controller()
{
	delete tilesController;
	QNode::clear(rootDynamic);
	QNode::clear(rootStatic);
}