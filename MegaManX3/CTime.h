
#include "ConstGlobals.h"
#ifndef _CTime_H_
#define _CTime_H_

enum ETime
{
	Stop = -1,
	Pause = 0,
	Run = 1
};

class CTime
{
private:
	unsigned long timeStart;
	unsigned long timeUp;

	ETime status;
public:
	CTime();
	CTime(unsigned long timeUp);
	void update();

	void setTimeUp(unsigned long timeUp);
	unsigned long getTimeUp();
	unsigned long getTime();

	void stop();
	void start();
	//void resume();

	bool isRunning();

	bool isStop();
	~CTime();
};

#endif // !_CTime_H_