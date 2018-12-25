#ifndef _Controller_H_

#define _Controller_H_

#include "GameObject.h"
#include "MegamanX.h"
#include "QNode.h"
#include "CollisionEvent.h"
#include "ScenceController.h"

#include "BarrierSystem.h"

#include "Elevator.h"
#include "Helit.h"

class Controller
{

private:
	MegamanX* main;

	unordered_map<int, GameObject*> currentStatic;//current Static objects
	unordered_map<int, GameObject*> currentDynamic;//current Dynaimc Objects;

	QNode* rootStatic;//static Objects
	QNode* rootDynamic;//dynamic Objects;
	GameObject* elevator;

	ScenceController* tilesControll;
	BarrierSystem* barrier;



public:
	Controller(MegamanX *main, QNode * rootStatic, QNode* rootDynamic);
	~Controller();
	void update(DWORD dt);
	void render(DWORD dt);
};

#endif // !_Controller_H_