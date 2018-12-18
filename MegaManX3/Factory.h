#ifndef _Factory_H_
#define _Factory_H_
#include <unordered_map>
#include <fstream>

#include "QNode.h"
#include "GameObject.h"
#include "NotorBanger.h"
#include "HeadGunner.h"
#include "Brick.h"
#include "CTreeObject.h"
#include "GameObject.h"
#include "Elevator.h"
#include "Helit.h"
using namespace std;
class Factory
{
private: static Factory* _instance;
public:
	static Factory* getInstance();
	Factory();
	~Factory();
	unordered_map<UINT, GameObject*>* createObjects(wchar_t* file);
	QNode* createQuadTree(wchar_t* fileQuadtree, unordered_map<UINT, GameObject*>& Objects);

private:
	vector<CTreeObject*>* getObject(ifstream * in, int numObjects, unordered_map<UINT, GameObject*>& objects);
};

#endif //_Factory_H_