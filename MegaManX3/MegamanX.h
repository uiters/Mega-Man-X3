#ifndef _MegamanX_H
#define _MegamanX_H
#include "DynamicObject.h"
#include "CKey.h"

class MegamanX :
	public DynamicObject,
	public CKey
{
public:
	MegamanX();
	~MegamanX();

public:
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;
};

#endif // !_MegamanX_H