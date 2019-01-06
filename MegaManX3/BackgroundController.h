#ifndef _BackgroundController_H_
#define _BackgroundController_H_

#include "Animation.h"
#include "ConstGlobals.h"

class BackgroundController
{
private:
	CAnimation* backgroundBoss;
	void loadResources();
public:
	BackgroundController();
	~BackgroundController();

public:
	void render(DWORD dt);
	void update(DWORD dt);
};

#endif // !_BackgroundController_H_