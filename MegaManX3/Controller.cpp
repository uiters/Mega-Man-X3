#include "Controller.h"


Controller::Controller(MegamanX* main, QNode * rootStatic, QNode * rootDynamic)
{
	this->rootStatic = rootStatic;
	this->rootDynamic = rootDynamic;
	this->collision = Collision::getInstance();
	this->main = main;
}

Controller::~Controller()
{
	QNode::clear(rootDynamic);
	QNode::clear(rootStatic);
}

void Controller::update(DWORD dt)
{
	rootStatic->getObjectsIn(viewPortGlobal, currentStatic);//current static 
	rootDynamic->getObjectsIn(viewPortGlobal, currentDynamic);//current dynamic 

	auto collisionStatic = collision->findCollisions(dt, main, currentStatic);
}

void Controller::render(DWORD dt)
{
}
