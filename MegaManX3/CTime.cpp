#include "CTime.h"



CTime::CTime()
{
	status = ETime::Stop;
	this->timeUp = 0;
	this->timeStart = 0;
}


CTime::CTime(unsigned long timeUp)
{
	status = ETime::Stop;
	this->timeUp = timeUp;
	this->timeStart = 0;
}

void CTime::update()
{
	if (status != 1) return;
	else
	{
		DWORD now = GetTickCount();

		if (timeUp == 0) return;
		if (now - timeStart >= timeUp) {
			stop();
		}
	}
}

unsigned long CTime::getTimeUp()
{
	return timeUp;
}

unsigned long CTime::getTime()
{
	return status == ETime::Run ? GetTickCount() - timeStart : 0;
}

void CTime::stop()
{
	status = ETime::Stop;
	this->timeStart = GetTickCount();
}

void CTime::start()
{
	status = ETime::Run;
	this->timeStart = GetTickCount();
}



bool CTime::isRunning()
{
	return status == ETime::Run;
}


bool CTime::isStop()
{
	return status == ETime::Stop;
}

void CTime::setTimeUp(unsigned long timeOff)
{
	this->timeUp = timeOff;
}

CTime::~CTime()
{
}
