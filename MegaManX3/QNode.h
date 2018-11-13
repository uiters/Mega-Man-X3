//#ifndef _QNode_H_
//#define _QNode_H_
//
//#include <memory>
//#include <vector>
//#include <unordered_set>
//
//#include "ConstGlobals.h"
//#include "CTreeObject.h"
//using namespace std;
//
//template <typename T> 
//class QNode
//{
//protected:
//	int _id;
//	CRectangle rect;
//	using Vect = vector< CTreeObject < T >*, allocator<CTreeObject < T >*>>;
//	Vect *objects;
//
//	QNode* topLeft;
//	QNode* topRight;
//	QNode* bottomLeft;
//	QNode* bottomRight;
//
//	void getObjects(CRectangle* region, unordered_set<T>* objs) {
//		if (this->topLeft != NULL)
//		{
//			if (this->topLeft->rect.intersectsWith(region))
//				this->topLeft->getObjects(region, objs);
//
//			if (this->topRight->rect.intersectsWith(region))
//				this->topRight->getObjects(region, objs);
//
//			if (this->bottomLeft->rect.intersectsWith(region))
//				this->bottomLeft->getObjects(region, objs);
//
//			if (this->bottomRight->rect.intersectsWith(region))
//				this->bottomRight->getObjects(region, objs);
//		}
//		else
//		{
//			CTreeObject<T>* obj;
//			for(obj : objects)
//			{
//				obj = objects[i];
//				objs->insert(obj->object);
//			}
//		}
//	}
//	void _insert(CTreeObject<T>* object)
//	{
//		objects->emplace_back(object);
//		if (objects->size() > 1 && this->rect.width > WIDTH_QUADTREE && this->rect.height > HEIGHT_QUATREE) //div
//		{
//			if (this->topLeft == NULL)
//			{
//				this->topLeft = new QNode<T>(this->_id * 10 + 1, this->rect.x, this->rect.y, this->rect.width / 2, this->rect.width / 2);
//				this->topRight = new QNode<T>(this->_id * 10 + 2, this->rect.centerX(), this->rect.y, this->rect.width / 2, this->rect.width / 2);
//				this->bottomLeft = new QNode<T>(this->_id * 10 + 3, this->rect.x, this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
//				this->bottomRight = new QNode<T>(this->_id * 10 + 4, this->rect.centerX(), this->rect.centerY(), this->rect.width / 2, this->rect.width / 2);
//			}
//			//CTreeObject<T>* obj = 0;ec
//			for (int i = 0; i < objects->size() ; ++i)
//			{
//				auto obj = objects[i];
//				if (topLeft->rect.intersectsWith(obj->region))
//					topLeft->_insert(obj);
//
//				if (topRight->rect.intersectsWith(obj->region))
//					topRight->_insert(obj);
//
//				if (bottomLeft->rect.intersectsWith(obj->region))
//					bottomLeft->_insert(obj);
//
//				if (bottomRight->rect.intersectsWith(obj->region))
//					bottomRight->_insert(obj);
//			}
//		}
//	}
//public:
//	QNode<T>(int id, int x, int y, int width, int height) : rect(x, y, width, height) {
//		_id = id;
//		objects = new vector< CTreeObject<T> * >();
//	}
//
//	void insert(T object, int x, int y, int width, int height)
//	{
//		CRectangle* r = new CRectangle(x, y, width, height);
//		CTreeObject<T>* o = new CTreeObject<T>(object, r);
//		_insert(o);
//	}
//	void insert(T object, CRectangle* rect)
//	{
//		CTreeObject<T>* o = new CTreeObject<T>(object, rect);
//		_insert(o);
//	}
//	void getObjectsIn(Viewport* viewport, unordered_set<T>* objs)
//	{
//		this->getObjects(viewport, objs);
//
//	}
//	void getCollision(CRectangle* rect, unordered_set<T>* objs)
//	{
//		this->getObjects(rect, objs);
//	}
//	~QNode() {}
//
//public: 
//	static void clear(QNode<T>* &node)
//	{
//		if (node->topLeft != NULL) {
//			clear(node->topLeft);
//			clear(node->topRight);
//			clear(node->bottomLeft);
//			clear(node->bottomRight);
//		}
//		delete node;
//		node = 0;
//	}
//};
//#endif // !_QNode_H_