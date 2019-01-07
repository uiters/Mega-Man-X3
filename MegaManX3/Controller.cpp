#include "Controller.h"


void Controller::filterAndUpdate(DWORD dt, unordered_map<int, GameObject*>& objects)
{
	for (auto i = objects.begin(); i != objects.end();)
	{
		GameObject* obj = (*i).second;
		if (obj->getBoundBox().intersectsWith(*viewPortGlobal))
		{
			obj->setReset();
			currentDynamic[0][obj->getID()] = obj;
			obj->update(dt, &currentStatic);
			//debugOut(L"%f %f \n", obj->x, obj->y);
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
	currentDynamic->clear();
	rootStatic->getObjectsIn(viewPortGlobal, currentStatic);// static quadtree
	stageController->getStaticObjects(currentStatic);//get static from stage

	background->update(dt);
	tilesController->update(viewPortGlobal);
	stageController->update(dt, &currentStatic);
	
	if (enableUpdate)
	{
		rootDynamic->getObjectsIn(viewPortGlobal, *saveDynamic);// dynamic quatree

		filterAndUpdate(dt, *saveDynamic);//filter Dynamic Object => current dynamic

		main->update(dt, &currentStatic, currentDynamic);
		
		stageController->getDynamicObjects(stageObjects);
		main->updateStage(dt, &stageObjects);

		//switch current -> save && save ->current
		auto temp = currentDynamic;
		currentDynamic = saveDynamic;
		saveDynamic = temp;
	}
	if(!hpBarBoss && cameraGlobal->getState() == 10)
		hpBarBoss = stageController->getHPBar();
}

void Controller::render(DWORD dt)
{
	background->render(dt);
	tilesController->render(dt);

	for (auto kv : *saveDynamic) 
	{
		kv.second->render(dt);
	}

	weaponEffect->render(dt); //render effect dynamic
	stageController->render(dt);
	main->render(dt);

	hpBarMain->render(true);

	if(hpBarBoss)
		hpBarBoss->render(true);
}


Controller::Controller(MegamanX* main, QNode * rootStatic, QNode * rootDynamic)
{
	stageController = StageController::getInstance();
	weaponEffect = WeaponEffectController::getIntance();
	background = new BackgroundController();
	tilesController = new ScenceController();
	hpBarMain = new HPBar(*main->getHp(), 38.0f, 2.0f, true);

	this->enableUpdate = true;
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->main = main;
	this->currentDynamic = &dynamicObject1;
	this->saveDynamic = &dynamicObject2;
	this->main->state = stand;

	stageController->setEnableUpdateController(&enableUpdate);
}

Controller::~Controller()
{
	delete tilesController;
	QNode::clear(rootDynamic);
	QNode::clear(rootStatic);
}