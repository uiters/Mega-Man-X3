#ifndef _Zero_H
#define _Zero_H
#include "DynamicObject.h"
#include "CKey.h"
class Zero :
	public DynamicObject,
	public CKey
{
public:
	Zero();
	~Zero();

public:
	void onKeyDown(int) override;
	void onKeyUp(int) override;
	void keyState(BYTE*) override;
};

#endif