#include "HPBar.h"

void HPBar::drawTail(int & y)
{
	tail->draw(x, y);
	y -= 16; // 16 is height body
}

void HPBar::drawBody(int & y)
{
	body->draw(x, y); // curent have body
	if (extraBody >= 0)
	{
		y -= extraY;
		for (int i = 0; i < extraBody; ++i)
		{
			body->draw(x, y);
			if (i != extraBody - 1)
				y -= 16; // 16 is height of body
		}
	}
	y -= 4;// 4 is height head
}

void HPBar::drawHead(int & y)
{
	head->draw(x, y);
	y = this->y - 2;// now hp start 0
}

void HPBar::drawEntry(int & y)
{
	if (*hp > 0.0f)
	{
		entries = *(this->hp) / step + 0.99999f;
		entries = entries > maxEntries ? maxEntries : entries;// sanitize input
	}
	else entries = 0;

	for (int i = 0; i < entries; ++i)
	{
		entry->draw(x, y);
		y -= 2;//2 is height entry
	}
}

HPBar::HPBar(float & hp, float maxHp, float step, bool isMegaman)
{
	this->hp = &hp;
	this->step = step;

	head = spritesGlobal->get(HpHead);
	body = spritesGlobal->get(HpBody);
	tail = spritesGlobal->get(isMegaman ? HpTailMain : HpTailBoss);
	entry = spritesGlobal->get(HpEntry);

	maxEntries = maxHp / step;
	extraBody = (UINT)(maxHp / step / 8); //round
	extraY = (maxEntries % 8) * 2;
	//
	if (!extraY)
	{
		extraY = 16;
		extraBody -= 1;
	}


 	x = isMegaman ? 10 : 246 - 14;
	y = 80;
}

//draw bottom to top
void HPBar::render(DWORD dt)
{
	int nextY = y ;

	drawTail(nextY);
	drawBody(nextY);
	drawHead(nextY);
	drawEntry(nextY);
}

HPBar::~HPBar()
{
}
