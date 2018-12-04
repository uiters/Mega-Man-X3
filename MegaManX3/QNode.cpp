#include "qnode.h"

void QNode::clear(QNode *& node)
{
	if (node->topLeft != NULL) {
		clear(node->topLeft);
		clear(node->topRight);
		clear(node->bottomLeft);
		clear(node->bottomRight);
	}
	for (auto e : node->dynamicObjects) delete e;
	for (auto e : node->staticObjects) delete e;
	delete node;
	node = 0;
}

QNode::QNode() : rect(0, 0, 0, 0)
{
}
QNode::QNode(UINT id, int x, int y, UINT width, UINT height) : rect(x, y, width, height) {
	_id = id;
}
void QNode::getObjects(CRectangle * region, unordered_set<CTreeObject*>* objs, bool isStatic)
{
	if (this->topLeft != NULL)
	{
		if (this->topLeft->rect.intersectsWith(region))
			this->topLeft->getObjects(region, objs, isStatic);

		if (this->topRight->rect.intersectsWith(region))
			this->topRight->getObjects(region, objs, isStatic);

		if (this->bottomLeft->rect.intersectsWith(region))
			this->bottomLeft->getObjects(region, objs, isStatic);

		if (this->bottomRight->rect.intersectsWith(region))
			this->bottomRight->getObjects(region, objs, isStatic);
	}
	else
	{
		if(isStatic)
			for (auto obj : staticObjects)
			{
				objs->insert(obj);
			}
		else for (auto obj : dynamicObjects)
		{
			objs->insert(obj);
		}
	}
}

void QNode::_insert(CTreeObject* object, bool isStatic)
{
	auto objects = isStatic ? &staticObjects : &dynamicObjects;
	objects->emplace_back(object);
	if (objects->size() > 1 && this->rect.width > WIDTH_QUADTREE && this->rect.height > HEIGHT_QUATREE && _level < Max_level) //div
	{
		if (this->topLeft == NULL)
		{
			this->topLeft = new QNode(this->_id * 10 + 1, this->rect.x, this->rect.y, this->rect.width / 2, this->rect.width / 2);
			this->topRight = new QNode(this->_id * 10 + 2, this->rect.centerX(), this->rect.y, this->rect.width / 2, this->rect.width / 2);
			this->bottomLeft = new QNode(this->_id * 10 + 3, this->rect.x, this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
			this->bottomRight = new QNode(this->_id * 10 + 4, this->rect.centerX(), this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
		}
		//CTreeObject<T>* obj = 0;ec
		for (int i = 0; i < objects->size(); ++i)
		{
			CTreeObject* obj = (*objects)[i];
			if (topLeft->rect.intersectsWith(&obj->region))
				topLeft->_insert(obj, isStatic);

			if (topRight->rect.intersectsWith(&obj->region))
				topRight->_insert(obj, isStatic);

			if (bottomLeft->rect.intersectsWith(&obj->region))
				bottomLeft->_insert(obj, isStatic);

			if (bottomRight->rect.intersectsWith(&obj->region))
				bottomRight->_insert(obj, isStatic);
		}
	}
}



void QNode::insert(LPObject object, int x, int y, UINT width, UINT height, bool isStatic)
{
	CRectangle* r = new CRectangle(x, y, width, height);
	CTreeObject* o = new CTreeObject(object, r);
	object->currentNode = o;
	_insert(o, isStatic);
}

void QNode::getObjectsIn(Viewport * viewport, unordered_set<CTreeObject*>* objs, bool isStatic)
{
	this->getObjects(&viewport->getRectangle(), objs, isStatic);
}

void QNode::getCollision(CRectangle * rect, unordered_set<CTreeObject*>* objs, bool isStatic)
{
	objs->clear();
	this->getObjects(rect, objs, isStatic);
}

void QNode::build(unordered_map<int, QNode*>& node)
{
	if (topLeft == NULL) {
		if (node[_id * 10 + 1] != NULL) {
			topLeft = node[_id * 10 + 1];
			topRight = node[_id * 10 + 2];
			bottomLeft = node[_id * 10 + 3];
			bottomRight = node[_id * 10 + 4];
		}
		else return;
	}
		topLeft->build(node);
		topRight->build(node);
		bottomLeft->build(node);
		bottomRight->build(node);
}

void QNode::add(vector<CTreeObject*>* objs, bool isStatic)
{
	isStatic ? staticObjects = *objs : dynamicObjects = *objs;
}




