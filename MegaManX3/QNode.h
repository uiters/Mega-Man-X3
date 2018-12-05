#ifndef _QNode_H_
#define _QNode_H_

#include <vector>
#include <unordered_set>

#include "ConstGlobals.h"
#include "CTreeObject.h"
#include "GameObject.h"
using namespace std;
#define Max_level 6
using namespace std;
class QNode
{
protected:
	UINT _id;
	int _level;
	CRectangle rect;
	vector<CTreeObject*> objects;

	QNode* topLeft;
	QNode* topRight;
	QNode* bottomLeft;
	QNode* bottomRight;

protected:
	void getObjects(CRectangle* region, unordered_map<int, CTreeObject*>& objs);
	void _getObjects(unordered_map<int, CTreeObject*>& objs);
	void _insert(CTreeObject* object);

	void createNode();

public:

	QNode(UINT id, int x, int y, UINT width, UINT height);

	void insert(LPObject object, int x, int y, UINT width, UINT height);

	void getObjectsIn(Viewport* viewport, unordered_map<int, CTreeObject*>& objs);


	void build(unordered_map<int, QNode*>& node);
	void add(const vector<CTreeObject*>& objs);

	int count();

	~QNode() {}

public: 
	static void clear(QNode* &node);

};
#endif // !_QNode_H_