#ifndef _HornetExplosion_H_
#define _HornetExplosion_H_
#include "Effect.h"

class HornetExplosion
	:public Effect
{
	void loadResources() override;
	static HornetExplosion* _instance;
	HornetExplosion();
public:
	~HornetExplosion();

public:
	static HornetExplosion* getInstance();
};
#endif // !_HornetExplosion_H_
