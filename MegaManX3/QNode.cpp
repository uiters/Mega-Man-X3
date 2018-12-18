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

void QNode::getObjectsIn(Viewport * viewport, unordered_map<int, GameObject*>& objs)
{
	objs.clear();
	this->getObjects(viewport, objs);
}

void QNode::getObjects(CRectangle * region, unordered_map<int, GameObject*>& objs)
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

void QNode::_getObjects(unordered_map<int, GameObject*>& objs) {
	int n = objects.size();
	int id = 0;
	for (int i = 0; i < n; ++i)
	{
		id = objects[i]->getID();
		objs[id] = objects[i];
	}
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

void QNode::add(const vector<GameObject*>& objs)
{
	objects = objs;
}

int QNode::count()
{
	if(topLeft == 0) return objects.size();
	return this->topLeft->count() + topRight->count() + bottomLeft->count() + bottomRight->count();
}

 



