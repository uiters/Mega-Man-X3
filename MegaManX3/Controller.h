#ifndef _Controller_H_
#define _Controller_H_
#include "GameObject.h"
#include "MegamanX.h"
#include "QNode.h"
#include "CollisionEvent.h"
class Controller
{

private:
	MegamanX* main;

	unordered_map<int, CTreeObject*> currentStatic;//current Static objects
	unordered_map<int, CTreeObject*> currentDynamic;//current Dynaimc Objects;

	QNode* rootStatic;//static Objects
	QNode* rootDynamic;//dynamic Objects;

	Collision* collision;
public:
	Controller(MegamanX *main, * rootStatic, QNode* rootDynamic);
	~Controller();

public:
	void update(DWORD dt);
	void render(DWORD dt);
};

#endif // !_Controller_H_