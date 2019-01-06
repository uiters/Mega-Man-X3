#ifndef _StageController_H_
#define _StageController_H_
#include "Camera.h"
#include "MegamanX.h"


class StageController
{
private:
	unordered_map<int, GameObject*>* currentStatic;//current Static objects
	unordered_map<int, GameObject*>* currentDynamic;//current Dynaimc Objects;
	Collision* collision;
	Elevator* elevator;
	Camera* camera;
	MegamanX* megaman;
	int wait = 0;
	bool isEnableElevator = false;
	bool* enableUpdateController;
	StageController();

	static StageController* _instance;
	bool isResetLocation = false;
private:
	void getStaticObject(DWORD dt);
	void getEnemies(DWORD dt);
public:
	static StageController* getInstance();
	~StageController();

public:
	void update(DWORD dt);
	void updateElevator(DWORD dt);
	
	void renderElevator(DWORD dt);

public:
	void setCurrentStatic(unordered_map<int, GameObject*>* currentStatic) { this->currentStatic = currentStatic; }
	void setCurrentDynamic(unordered_map<int, GameObject*>* currentDynamic) { this->currentDynamic = currentDynamic; }

	void setEnableUpdateController(bool* enable) { this->enableUpdateController = enable; }
	void setElevator(Elevator* elevator) { this->elevator = elevator; }
};

#endif // !_StageController_H_