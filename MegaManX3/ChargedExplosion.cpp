#include "ChargedExplosion.h"



void ChargedExplosion::loadResources()
{

}

ChargedExplosion::ChargedExplosion()
{
	loadResources();
}
ChargedExplosion * ChargedExplosion::_instance = null;

ChargedExplosion * ChargedExplosion::getInstance()
{
	if (_instance == null)_instance = new ChargedExplosion();
	return _instance;
}

ChargedExplosion::~ChargedExplosion()
{
}
