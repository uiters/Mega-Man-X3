#include "qnode.h"

void QNode::clear(QNode *& node)
{
	if (node->topLeft != NULL) {
		clear(node->topLeft);
		clear(node->topRight);
		clear(node->bottomLeft);
		clear(node->bottomRight);
	}
	for (auto e : node->objects) delete e;
	delete node;
	node = 0;
}

QNode::QNode(UINT id, int x, int y, UINT width, UINT height) : rect(x, y, width, height) 
{
	_id = id;
}

void QNode::getObjectsIn(Viewport * viewport, unordered_map<int, CTreeObject*>& objs)
{
	this->getObjects(viewport, objs);
}

void QNode::getObjects(CRectangle * region, unordered_map<int, CTreeObject*>& objs)
{
	if (this->topLeft != NULL) // not leaf
	{
		if (this->topLeft->rect.intersectsWith(*region))
			this->topLeft->getObjects(region, objs);

		if (this->topRight->rect.intersectsWith(*region))
			this->topRight->getObjects(region, objs);

		if (this->bottomLeft->rect.intersectsWith(*region))
			this->bottomLeft->getObjects(region, objs);

		if (this->bottomRight->rect.intersectsWith(*region))
			this->bottomRight->getObjects(region, objs);
	}
	else
	{
		_getObjects(objs);
	}
}

void QNode::_getObjects(unordered_map<int, CTreeObject*>& objs) {
	int n = objects.size();
	int id = 0;
	for (int i = 0; i < n; ++i)
	{
		id = objects[i]->object->getID();
		objs[id] = objects[i];
	}
}

void QNode::_insert(CTreeObject* object)
{
	objects.emplace_back(object);
	int size = objects.size();
	if (topLeft == 0)
	{
		createNode();
	}
	else
	{
		for (int i = 0; i < objects.size(); ++i)
		{
			CTreeObject* obj = (objects)[i];
			if (topLeft->rect.intersectsWith(obj->region))
				topLeft->_insert(obj);

			if (topRight->rect.intersectsWith(obj->region))
				topRight->_insert(obj);

			if (bottomLeft->rect.intersectsWith(obj->region))
				bottomLeft->_insert(obj);

			if (bottomRight->rect.intersectsWith(obj->region))
				bottomRight->_insert(obj);
		}
	}

}

void QNode::createNode() {
	if (objects.size() > 1 && this->rect.width > WIDTH_QUADTREE && this->rect.height > HEIGHT_QUATREE && _level < Max_level) //div
	{
		this->topLeft = new QNode(this->_id * 10 + 1, this->rect.x, this->rect.y, this->rect.width / 2, this->rect.width / 2);
		this->topRight = new QNode(this->_id * 10 + 2, this->rect.centerX(), this->rect.y, this->rect.width / 2, this->rect.width / 2);
		this->bottomLeft = new QNode(this->_id * 10 + 3, this->rect.x, this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
		this->bottomRight = new QNode(this->_id * 10 + 4, this->rect.centerX(), this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
	}
}

void QNode::insert(LPObject object, int x, int y, UINT width, UINT height)
{
	CRectangle r = CRectangle(x, y, width, height);
	CTreeObject* o = new CTreeObject(object, r);
	object->currentNode = o;
	_insert(o);
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

void QNode::add(const vector<CTreeObject*>& objs)
{
	objects = objs;
}

int QNode::count()
{
	if(topLeft == 0) return objects.size();
	return this->topLeft->count() + topRight->count() + bottomLeft->count() + bottomRight->count();
}

 



