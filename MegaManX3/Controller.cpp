#include "Controller.h"
#include "CollisionEvent.h"
#include "NotorBanger.h"
Controller::Controller(MegamanX* main, QNode * rootStatic, QNode * rootDynamic)
{
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->main = main;
	tilesControll = new ScenceController();
	main->state = stand;
	shurikein  = new Shurikein(TShurikein, 2402, 920);
	shurikein->state = manifest;
}

Controller::~Controller()
{
	delete tilesControll;
	QNode::clear(rootDynamic);
	QNode::clear(rootStatic);
}

void Controller::update(DWORD dt)
{
	tilesControll->update(viewPortGlobal);

	rootStatic->getObjectsIn(viewPortGlobal, currentStatic);//current static 
	rootDynamic->getObjectsIn(viewPortGlobal, currentDynamic);//current dynamic 

	//currentDynamic[-1] = Chelit;
	for (auto i = currentDynamic.begin(); i != currentDynamic.end();)
	{
		GameObject* obj = (*i).second->object;
		if (obj->getBoundingBox().intersectsWith(*viewPortGlobal))
		{
			obj->update(dt, &currentStatic);
			++i;
		}
		else i = currentDynamic.erase(i);
	}

	if (elevator)
	{
		elevator->object->update(dt);
		currentStatic[elevator->object->getID()] = elevator;
	}
	else
	{
		for (auto kv : currentStatic) {
			if (dynamic_cast<Elevator*>(kv.second->object))
			{
				elevator = kv.second;
			}
		}
	}
	//helit->update(dt, &currentStatic, &currentDynamic);

	shurikein->update(dt, &currentStatic);
	main->update(dt, &currentStatic, &currentDynamic);
}

void Controller::render(DWORD dt)
{
	tilesControll->render(dt);
	for (auto kv : currentDynamic) {
		kv.second->object->render(dt);
	}
	for each (auto item in currentStatic)
	{
		item.second->object->render(dt);
	}
	if (elevator) elevator->object->render(dt);
	main->render(dt);
	shurikein->render(dt);
	//helit->render(dt);
}
