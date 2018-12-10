#ifndef _DashSmoke_H_
#define _DashSmoke_H_
#include "Effect.h"
#include <vector>
#include "AnimationOneTime.h"

using namespace std;
class DashSmoke : public Effect
{
private:
	void loadResources() override;
	static DashSmoke* _instance;
	DashSmoke();
public:
	~DashSmoke();
	static DashSmoke* getInstance();
};
#endif // !_DashSmoke_H_
