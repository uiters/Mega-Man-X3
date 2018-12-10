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
public:
	~DashSpark();
	static DashSpark* getInstance();
};

#endif // !_DashSpark_H_