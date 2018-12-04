#include "CTime.h"



CTime::CTime()
{
	status = ETime::Stop;
	this->timeOff = 0;
	this->timeStart = 0;
}


CTime::CTime(unsigned long timeOff)
{
	status = ETime::Stop;
	this->timeOff = timeOff;
	this->timeStart = 0;
}

void CTime::update()
{
	if (status != 1) return;
	else
	{
		DWORD now = GetTickCount();
		if (timeOff == 0) return;
		if (now - timeStart >= timeOff) {
			stop();
		}
	}
}

unsigned long CTime::getTimeOff()
{
	return timeOff;
}

unsigned long CTime::getTime()
{
	return GetTickCount() - timeStart;
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

void CTime::pause()
{
	status = ETime::Pause;
}

void CTime::resume()
{
	if (isPause())
		status = ETime::Run;
}

bool CTime::isRunning()
{
	return status == ETime::Run;
}

bool CTime::isPause()
{
	return status == ETime::Pause;
}

bool CTime::isStop()
{
	return status == ETime::Stop;
}

void CTime::setTimeOff(unsigned long timeOff)
{
	this->timeOff = timeOff;
}

CTime::~CTime()
{
}
