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
<<<<<<< HEAD

	barrier = new BarrierSystem();

	//shurikein = new Shurikein(TShurikein, 2402, 920);
	//shurikein->state = manifest;
=======
	shurikein  = new Shurikein(TShurikein, 2518, 920);
	shurikein->state = manifest;
	brick1 = new Brick(0, 2297, 895, 22, 52);
	brick2 = new Brick(0, 2546, 895, 22, 52);
>>>>>>> d35ec485b7366bdabed9bb0cf9e2743e3b5af9f4
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

	//currentDynamic[-1] = shurikein;
	for (auto i = currentDynamic.begin(); i != currentDynamic.end();)
	{
		GameObject* obj = (*i).second;
		if (obj->getBoundBox().intersectsWith(*viewPortGlobal))
		{
			obj->update(dt, &currentStatic);
			++i;
		}
		else i = currentDynamic.erase(i);
	}

	if (elevator)
	{
		elevator->update(dt);
		currentStatic[elevator->getID()] = elevator;
	}
	else
	{
		for (auto kv : currentStatic) {
			elevator = dynamic_cast<Elevator*>(kv.second);
			if (elevator) break;
		}
	}
<<<<<<< HEAD

=======
	//helit->update(dt, &currentStatic, &currentDynamic);
>>>>>>> d35ec485b7366bdabed9bb0cf9e2743e3b5af9f4
	main->update(dt, &currentStatic, &currentDynamic);

	//helit->update(dt, &currentStatic, &currentDynamic);
	//shurikein->update(dt, &currentStatic);

	barrier->update(dt);
}

void Controller::render(DWORD dt)
{
	tilesControll->render(dt);
	for (auto kv : currentDynamic) {
		kv.second->render(dt);
	}
	for each (auto item in currentStatic)
	{
		item.second->render(dt);
	}
	if (elevator) elevator->render(dt);
	main->render(dt);

	//shurikein->render(dt);
	//helit->render(dt);

	barrier->render(dt);
}
