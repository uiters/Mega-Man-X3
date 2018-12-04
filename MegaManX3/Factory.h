#ifndef _Factory_H_
#define _Factory_H_
#include "QNode.h"
#include "GameObject.h"
#include <unordered_map>
#include <fstream>
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