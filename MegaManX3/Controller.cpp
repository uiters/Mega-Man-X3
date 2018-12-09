#include "Controller.h"

#include "NotorBanger.h"
Controller::Controller(MegamanX* main, QNode * rootStatic, QNode * rootDynamic)
{
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->main = main;
	tilesControll = new ScenceController(1);
	main->state = stand;
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
	for (auto kv : currentDynamic) {
		//auto obj = dynamic_cast<NotorBanger*>(kv.second->object);
		//if (obj)
		//	obj->update(dt);
		kv.second->object->update(dt);
	}
	
	//debugOut(L"%i\n", collisionStatic.size());
	main->update(dt, &currentStatic, 0);
}

void Controller::render(DWORD dt)
{

	tilesControll->render(dt);

	for (auto kv : currentDynamic) {
		//auto obj = dynamic_cast<NotorBanger*>(kv.second->object);
		//if (obj)
//obj->render(dt);
		kv.second->object->render(dt);
	}
	main->render(dt);
}
