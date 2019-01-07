#ifndef _Controller_H_

#define _Controller_H_

#include "MegamanX.h"
#include "QNode.h"
#include "CollisionEvent.h"
#include "ScenceController.h"
#include "Shurikein.h"
#include "StageController.h"
#include "WeaponEffectController.h"
#include "BackgroundController.h"
#include "CollisionEvent.h"
#include "NotorBanger.h"
#include "StageController.h"

class Controller
{

private:
	MegamanX* main;
	BackgroundController* background;

	unordered_map<int, GameObject*>* currentDynamic;//current Dynaimc Objects;
	unordered_map<int, GameObject*>* saveDynamic;//save

	unordered_map<int, GameObject*> dynamicObject1;
	unordered_map<int, GameObject*> dynamicObject2;
	unordered_map<int, GameObject*> stageObjects; //state objects
	unordered_map<int, GameObject*> currentStatic;//current Static objects

	StageController* stageController;
	ScenceController* tilesController;
	WeaponEffectController* weaponEffect;
	QNode* rootStatic;//static Objects
	QNode* rootDynamic;//dynamic Objects;
	bool enableUpdate;

	HPBar* hpBarMain;
	HPBar* hpBarBoss;

private:
	void filterAndUpdate(DWORD dt, unordered_map<int, GameObject*>& objects);
public:
	Controller(MegamanX *main, QNode * rootStatic, QNode* rootDynamic);
	~Controller();
	void update(DWORD dt);
	void render(DWORD dt);
};

#endif // !_Controller_H_