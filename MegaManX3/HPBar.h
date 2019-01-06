#ifndef _HPBar_H_
#define _HPBar_H_

#include "ConstGlobals.h"
#include "Sprites.h"
class HPBar
{
private:
	float *hp;
	float step;

	int extraY;
	unsigned int extraBody;
	int entries;
	int maxEntries;

	CSprite* head;
	CSprite* tail;
	CSprite* body;
	CSprite* entry;

	int x, y;
	void drawTail(int& y);
	void drawBody(int& y);
	void drawHead(int& y);
	void drawEntry(int& y);
public:

	HPBar(float &hp, float maxHp, float step, bool isMegaman);
	void render(DWORD dt);
	~HPBar();

};

#endif // !_HPBar_H_