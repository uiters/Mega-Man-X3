#ifndef _QNode_H_
#define _QNode_H_

#include <vector>
#include <unordered_map>

#include "ConstGlobals.h"
#include "GameObject.h"

using namespace std;
class QNode
{
protected:
	UINT _id;
	int _level;
	CRectangle rect;
	vector<GameObject*> objects;

	QNode* topLeft;
	QNode* topRight;
	QNode* bottomLeft;
	QNode* bottomRight;

protected:
	void getObjects(CRectangle* region, unordered_map<int, GameObject*>& objs);
	void _getObjects(unordered_map<int, GameObject*>& objs);
public:

	QNode(UINT id, int x, int y, UINT width, UINT height);


	void getObjectsIn(Viewport* viewport, unordered_map<int, GameObject*>& objs);


	void build(unordered_map<int, QNode*>& node);
	void add(const vector<GameObject*>& objs);

	int count();

	~QNode() {}

public: 
	static void clear(QNode* &node);

};
#endif // !_QNode_H_