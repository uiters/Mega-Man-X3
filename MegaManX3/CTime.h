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
	unsigned long time;
	unsigned long timeOff;

	ETime status;
public:
	CTime();
	CTime(unsigned long timeOff);
	void update();

	void setTimeOff(unsigned long timeOff);
	unsigned long getTimeOff();
	unsigned long getTime();

	void stop();
	void start();
	void pause();
	void resume();

	bool isRunning();
	bool isPause();
	bool isStop();
	~CTime();
};

#endif // !_CTime_H_