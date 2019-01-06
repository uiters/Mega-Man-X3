#ifndef _BackgroundController_H_
#define _BackgroundController_H_

#include "Animation.h"
#include "ConstGlobals.h"
#include "Background.h"
class BackgroundController
{
private:

	void loadResources();
	unordered_map<int, Background*> backgrounds;
	Background* currentBackground;
	Background* preBackground;
public:
	BackgroundController();
	~BackgroundController();

public:
	void render(DWORD dt);
	void update(DWORD dt);
};

#endif // !_BackgroundController_H_