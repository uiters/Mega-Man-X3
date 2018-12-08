#include "Effect.h"



Effect::Effect(UINT idAnimation) : GameObject(0, 0, 0)
{
	LPANIMATION animation = CAnimations::getInstance()->get(idAnimation);
}

Effect::~Effect()
{
}
