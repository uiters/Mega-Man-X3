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

void Controller::updateItems(DWORD dt)
{
	for (auto it = items.begin(); it != items.end();)
	{
		it[0]->update(dt, &currentStatic);

		if (!it[0]->visible ||
			!it[0]->getBoundBox().intersectsWith(cameraGlobal->viewport))
		{
			delete (*it);
			it = items.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Controller::renderItems(DWORD dt)
{
	for (auto it = items.begin(); it != items.end(); ++it)
	{
		it[0]->render(dt);
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
	updateItems(dt);
	if(cameraGlobal->getState() == 10)
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

	renderItems(dt);

	main->render(dt);

	auto hornetPoint = stageController->getHornetPoit();
	if (hornetPoint)
		hornetPoint->render(dt);

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
	hpBarMain = new HPBar(*main->getHp(), 24.0f, 1.2f, true);

	this->enableUpdate = true;
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->main = main;
	this->currentDynamic = &dynamicObject1;
	this->saveDynamic = &dynamicObject2;
	this->main->state = stand;

	stageController->setEnableUpdateController(&enableUpdate);
	main->setItems(&items);
}

Controller::~Controller()
{
	delete tilesController;
	QNode::clear(rootDynamic);
	QNode::clear(rootStatic);
}