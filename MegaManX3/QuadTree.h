#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#define MAX_LEVEL 5

class GameObject;

#define Object GameObject

enum TYPE_RECT { TR_NONE, TR_TL, TR_TR, TR_BL, TR_BR };

class QuadTree
{
private:
	int checkInChildRect(RECT rInner);
	QuadTree** getChildNodeFromChildRect(char childRectType);
	bool IsExistActive( Object * obj);
	bool IsContainable( Object * obj);

public:
	int level;
	RECT region;
	list<Object *> staticObject;
	list<Object *> activeObject;

	QuadTree* topLeft;
	QuadTree* topRight;
	QuadTree* bottomLeft;
	QuadTree* bottomRight;

	QuadTree(int level, int x, int y, int size) {
		RECT r = { x,y,x + size,y + size };
		region = r;
		this->level = level;
		topLeft = topRight = bottomLeft = bottomRight = NULL;
	}
	QuadTree(int level, RECT region) : level(level), region(region) {}

	~QuadTree();

	void add(Object* obj, bool isStatic);
	void getObjectsAllNode(list<Object*>* staticList, list<Object*>* activeList);
	void getObjectsAllNode(list<Object*>* list, bool isStatic);
	void getObjectsFromCamera(RECT camera, list<Object*>* staticList, list<Object*>* activeList);
	void deleteObject(Object* object, bool isStatic);
	void Update();
	void Update(list<Object*> list);

	static bool rectInRect(RECT a, RECT b);
	RECT* getChildRect(RECT rect, int typeRect);

private:
	void getObjectsInNode(list<Object*>* list, bool isStatic);
	void getObjectsInNode(list<Object*>* staticList, list<Object*>* activeList);

};



