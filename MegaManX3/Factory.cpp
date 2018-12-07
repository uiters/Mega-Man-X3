#include "Factory.h"
#include "Brick.h"
#include "CTreeObject.h"
#include "GameObject.h"
Factory * Factory::_instance = 0;

Factory* Factory::getInstance()
{
	if(_instance == 0)
		_instance = new Factory();
	return _instance;
}

Factory::Factory()
{
}


Factory::~Factory()
{
}

unordered_map<UINT, GameObject*>*Factory::createObjects(wchar_t * file)
{
	unordered_map<UINT, GameObject*>*objs = new unordered_map<UINT, GameObject*>();
	ifstream input;
	input.open(file, ifstream::in);
	UINT id, idNameObject, idTypeObject, x, y, width, height;
	GameObject *obj;
	if (!input.good())
	{
		debugOut(L"[Failed] Load File ");
		return objs;
	}
	while (input)
	{
		input >> id >> idNameObject >> idTypeObject >> x >> y >> width >> height;
		//if (id == 2) continue;
		obj = new Brick(id, x, y, width, height);
		(*objs)[id] = obj;
	}
	input.close();
	return objs;
}


QNode * Factory::createQuadTree(wchar_t* fileQuadtree, unordered_map<UINT, GameObject*>& objects)
{
	QNode * root = 0;
	unordered_map<int, QNode*> node;
	ifstream input;
	input.open(fileQuadtree, ifstream::in);
	if (!input.good())
	{
		debugOut(L"[Failed] Load File ");
		return root;
	}
	UINT id, x, y, width, height, numNode, numObjects;
	input >> id >> x >> y >> width >> height >> numNode >> numObjects;
	vector<CTreeObject*>* listObject = getObject(&input, numObjects, objects);
	root = new QNode(id, x, y, width, height);

	root->add(*listObject);
	delete listObject;

	if (numNode == 0) return root;
	while (input) {
		input >> id >> x >> y >> width >> height >> numNode >> numObjects;
		listObject = getObject(&input, numObjects, objects);
		node[id] = new QNode(id, x, y, width, height);
		node[id]->add(*listObject);
		delete listObject;
	}
	root->build(node);
	return root;
}

vector<CTreeObject*>* Factory::getObject(ifstream  *input, int numObjects, unordered_map<UINT, GameObject*>& objects) {
	int id;
	vector<CTreeObject*>* vObjects = new vector<CTreeObject*>();
	for (int i = 0; i < numObjects; ++i)
	{
		(*input) >> id;
		CTreeObject *cObject = new CTreeObject(objects[id], *objects[id]->getBoundingBox());
		vObjects->push_back(cObject);
	}
	return vObjects;
}

