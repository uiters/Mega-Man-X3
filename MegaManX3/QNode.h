#ifndef _QNode_H_
#define _QNode_H_

#include <vector>
#include <unordered_set>

#include "ConstGlobals.h"
#include "CTreeObject.h"
#include "GameObject.h"
using namespace std;
#define Max_level 5
using namespace std;
class QNode
{
protected:
	UINT _id;
	int _level;
	CRectangle rect;
	vector<CTreeObject*> dynamicObjects;
	vector<CTreeObject*> staticObjects;

	QNode* topLeft;
	QNode* topRight;
	QNode* bottomLeft;
	QNode* bottomRight;

protected:
	void getObjects(CRectangle* region, unordered_set<CTreeObject*>* objs, bool isStatic);
	void _insert(CTreeObject* object, bool isStatic);
public:
	QNode();
	QNode(UINT id, int x, int y, UINT width, UINT height);
	void insert(LPObject object, int x, int y, UINT width, UINT height, bool isStatic);
	void getObjectsIn(Viewport* viewport, unordered_set<CTreeObject*>* objs, bool isStatic);
	void getCollision(CRectangle* rect, unordered_set<CTreeObject*>* objs, bool isStatic);
	void build(unordered_map<int, QNode*>& node);
	void add(vector<CTreeObject*>* objs, bool isStatic);
	~QNode() {}

public: 
	static void clear(QNode* &node);

};
#endif // !_QNode_H_