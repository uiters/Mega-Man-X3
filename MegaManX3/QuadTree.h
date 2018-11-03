#pragma once
#include "GameObject.h"
#include <d3dx9.h>

class GameObject;


#define Object GameObject
enum TYPE_RECT { TR_NONE, TR_TL, TR_TR, TR_BL, TR_BR };


class QuadTree
{
private:
	UINT nodeID;

private:
	int checkInChildRect(RECT rInner);
	QuadTree** getChildNodeFromChildRect(char childRectType);
	bool IsExistActive( Object * obj);
	bool IsContainable( Object * obj);

	void getObjectsInNode(list<Object*>* list, bool isStatic);
	void getObjectsInNode(list<Object*>* staticList, list<Object*>* activeList);

public:
	int level;
	RECT region;
	list<Object *> staticObject;
	list<Object *> activeObject;

	QuadTree* topLeft;
	QuadTree* topRight;
	QuadTree* bottomLeft;
	QuadTree* bottomRight;

	QuadTree(UINT id, int level, int x, int y, int size);
	QuadTree(UINT id, int level, RECT region);

	~QuadTree();

	void add(Object* obj, bool isStatic);
	void getObjectsAllNode(list<Object*>* staticList, list<Object*>* activeList);
	void getObjectsAllNode(list<Object*>* list, bool isStatic);
	void getObjectsFromCamera(RECT camera, list<Object*>* staticList, list<Object*>* activeList);
	void deleteObject(Object* object, bool isStatic);
	void Update();
	void Update(list<Object*> list);

	static bool rectInRect(RECT a, RECT b);
	RECT getChildRect(RECT rect, int typeRect);

	 
};



