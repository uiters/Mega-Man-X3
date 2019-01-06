#include "SolskjærController.h"


SolskjærController::SolskjærController()
{
	barrier = new BarrierSystem();
	solskjær = new Solskjær();
	carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);

	isOnlyOne = true;
	isDisplayBoss = false;
	clock = 0;
	clockForCarryArm = 0;
	clockForSolskjær = 0;
	limitTime = 2500;
}


SolskjærController::~SolskjærController()
{
}

void SolskjærController::update(DWORD dt, unordered_map<int, GameObject*>* staticObject, MegamanX* main)
{
	this->staticObject = staticObject;
	objects.clear();
	barrier->update(dt);
	
	if (!barrier->isHidden) {
		if (barrier->y >= 855) {
			generateCarryArm(dt);
			generateSolskjær(dt);
			if (!isDisplayBoss) {
				clock++;
				if (clock > limitTime) {
					if (( carryArmFirst->isComplete && carryArmSecond != NULL && carryArmSecond->isComplete ) ||
						(carryArmFirst->isComplete && carryArmSecond == NULL) ||
						(carryArmFirst->isDie[0] && carryArmSecond != NULL && carryArmSecond->isDie[0]) ||
						(carryArmFirst->isDie[0] && carryArmSecond == NULL)
					)
						barrier->isHidden = true;
				}
			}
			else clock = 0;
		}
	}
	//if (solskjær->isDie) barrier->isHidden = true;

	if (carryArmFirst)
		objects[4] = carryArmFirst->getBox(),
		objects[2] = carryArmFirst;

	if (carryArmSecond)
		objects[5] = carryArmSecond->getBox(),
		objects[3] = carryArmSecond;
	objects[1] = solskjær;
	collisionMain(main);
}

void SolskjærController::render(DWORD dt)
{
	if (!barrier->isHidden) {
		solskjær->render(dt);
		barrier->render(dt);
		carryArmFirst->render(dt);

		if (carryArmSecond != NULL) carryArmSecond->render(dt);
	}
	else
	{
		barrier->render(dt);
	}
}

void SolskjærController::collisionMain(MegamanX* main)
{
	bulletCollisionDynamic(main);//like main bullet collision dynamic
	if (main->protect()) return;
	dynamicCollisionMain(main); //like dynamic obejct bullet collision this
}

void SolskjærController::bulletCollisionDynamic(MegamanX* main)
{
	auto dynamicObjects = &objects;
	for (auto it = dynamicObjects->begin(); it != dynamicObjects->end(); )
	{
		if (!(*it).second) return; //null

		DynamicObject* obj = dynamic_cast<DynamicObject*>((*it).second);
		
		// bullet main collision enemies or boss (use single & swept aabb)
		auto objBox = obj->getBoundBox();
		auto weapons = main->getWeapons();
		for (auto bullet = weapons->begin(); bullet != weapons->end();)
		{
			if (obj->isDeath()) break;
			if (bullet[0]->getBoundBox().intersectsWith(objBox) //single aabb collision
				||
				main->collisionGameObject(*bullet, obj)) //colision bullet with dynamic with swept aabb
			{
				obj->receiveDamage(bullet[0]->getDamage());
				if (obj->isDeath())
				{
					if (dynamic_cast<BusterShot*>(*bullet)) // don't cross delete bullet
					{
						delete *bullet;
						bullet = weapons->erase(bullet);
					}
				}
				else
				{
					delete *bullet;
					bullet = weapons->erase(bullet);
				}
				break;// out for bullet
			}
			else // bullet main collision bullet enemies or boss (use swept aabb)
			{
				++bullet;
			}
		}
		++it;
	}
}

void SolskjærController::dynamicCollisionMain(MegamanX* main)
{
	auto megamanBox = main->getBoundBox();
	auto dynamicObjects = &objects;//dynamic object

	for (auto kv : *dynamicObjects)
	{
		// object collision main (include bullet) (use single & swept aabb)
		DynamicObject* obj = dynamic_cast<DynamicObject*>(kv.second);
		if (!obj || obj->isDeath() || !obj->visible) continue;

		if (kv.second->getBoundBox().intersectsWith(megamanBox) //single
			||
			main->collisionGameObject(obj, main)) // swpet
		{
			main->setHurt();
			return;
		}

		auto bullets = obj->getWeapons();
		for (auto bullet = bullets->begin(); bullet != bullets->end(); )
		{
			if (bullet[0]->getBoundBox().intersectsWith(megamanBox) //single
				||
				main->collisionBullet(*bullet, main)) //swept
			{
				if (bullet[0]->toLeft)
					obj->createExplosion(bullet[0]->x + 10, bullet[0]->y);
				else
					obj->createExplosion(bullet[0]->x - 10, bullet[0]->y);
				delete *bullet;
				bullet = bullets->erase(bullet);
				main->setHurt();
				return;
			}
			else ++bullet;
		}
	}
}

void SolskjærController::generateCarryArm(DWORD dt)
{
	if (carryArmFirst->getBox()->getIsDeath()) {
		clockForCarryArm++;
		if (clockForCarryArm > 300) {
			carryArmFirst = new CarryArm(barrier->initX + 36, barrier->initY - 20, false);
			carryArmFirst->getBox()->setIsDeath(false);
			//objects[2] = carryArmFirst;

			this->isOnlyOne = true;

			clockForCarryArm = 0;
		}
	}
	
	if ((carryArmSecond == NULL && !carryArmFirst->getBox()->getIsDeath() && carryArmFirst->isComplete ) ||
		carryArmSecond != NULL && carryArmSecond->getBox()->getIsDeath()
	) {
		if (this->isOnlyOne) {
			clockForCarryArm++;
			if (clockForCarryArm > 300) {
				carryArmSecond = new CarryArm(barrier->initX + 36, barrier->initY - 20, true);
				carryArmSecond->getBox()->setIsDeath(false);
				//objects[3] = carryArmSecond;

				this->isOnlyOne = false;

				clockForCarryArm = 0;
			}
		}
	}

	carryArmFirst->update(dt);
	if (carryArmSecond != NULL) carryArmSecond->update(dt);
}

void SolskjærController::generateSolskjær(DWORD dt)
{
	if (carryArmSecond != NULL && 
		!carryArmFirst->getBox()->getIsDeath() && 
		!carryArmSecond->getBox()->getIsDeath() && 
		carryArmFirst->isComplete &&
		carryArmSecond->isComplete
	) {
		clockForSolskjær++;
		if (clockForSolskjær >= 700) {
			solskjær = new Solskjær();
			clockForSolskjær = 0;
			isDisplayBoss = true;
		}
		solskjær->update(dt, staticObject);
		objects[1] = solskjær;
	}

	if (carryArmSecond != NULL &&
		( carryArmFirst->getBox()->getIsDeath() || carryArmSecond->getBox()->getIsDeath() ) && 
		carryArmFirst->isComplete &&
		carryArmSecond->isComplete
	){
		if (solskjær->isRepeat) solskjær->reset();
		clockForSolskjær++;
		if (clockForSolskjær >= 700) {
			solskjær->isRepeat = false;
			clockForSolskjær = 0;
			isDisplayBoss = false;
		}
		solskjær->update(dt, staticObject);
		//objects[1] = solskjær;
	}
}
