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
#include "Shurikein.h"

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
<<<<<<< HEAD

	BarrierSystem* barrier;

=======
	Brick* brick1;
	Brick* brick2;
>>>>>>> d35ec485b7366bdabed9bb0cf9e2743e3b5af9f4
	Shurikein* shurikein;


public:
	Controller(MegamanX *main, QNode * rootStatic, QNode* rootDynamic);
	~Controller();
	void update(DWORD dt);
	void render(DWORD dt);
};

#endif // !_Controller_H_