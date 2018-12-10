#ifndef _DashSpark_H_
#define _DashSpark_H_

#include "Effect.h"
class DashSpark :
	public Effect
{
private:
	void loadResources() override;
	static DashSpark* _instance;
	DashSpark();
	bool isLeft = false;
public:
	~DashSpark();
	void setDirection(bool isLeft);
	void render(DWORD dt, bool center, D3DCOLOR colorBrush = WHITE(255));
	static DashSpark* getInstance();
};

#endif // !_DashSpark_H_