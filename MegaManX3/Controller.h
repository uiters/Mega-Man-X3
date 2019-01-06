#ifndef _Controller_H_

#define _Controller_H_

#include "GameObject.h"
#include "MegamanX.h"
#include "QNode.h"
#include "CollisionEvent.h"
#include "ScenceController.h"

#include "SolskjærController.h"

#include "Elevator.h"
#include "Helit.h"
#include "Genjibo.h"

#include "Shurikein.h"
#include "StageController.h"
#include "WeaponEffectController.h"
#include "BlastHornet.h"
#include "BackgroundController.h"
class Controller
{

private:
	MegamanX* main;
	BackgroundController* background;
	unordered_map<int, GameObject*> currentStatic;//current Static objects
	unordered_map<int, GameObject*> currentDynamic;//current Dynaimc Objects;
	StageController* stageController;
	ScenceController* tilesController;
	WeaponEffectController* weaponEffect;
	QNode* rootStatic;//static Objects
	QNode* rootDynamic;//dynamic Objects;
	GameObject* elevator;
	bool enableUpdate;
	BlastHornet* blastHornet;
	Brick* brick1;
	Brick* brick2;
	Genjibo* genjibo;
	Shurikein* shurikein;
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