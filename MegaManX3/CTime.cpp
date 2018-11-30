#include "CTime.h"



CTime::CTime()
{
	status = ETime::Stop;
	this->timeOff = 0;
	this->time = 0;
}

CTime::CTime(unsigned long timeOff)
{
	status = ETime::Stop;
	this->timeOff = timeOff;
	this->time = 0;
}

void CTime::update()
{
	if (status != 1) return;
	{
		time += GetTickCount();
		if (timeOff == 0) return;
		if (timeOff < time) {
			stop();
		}
	}
}

void CTime::setTimeOff(unsigned long timeOff)
{
	this->timeOff = timeOff;
}

unsigned long CTime::getTimeOff()
{
	return timeOff;
}

unsigned long CTime::getTime()
{
	return time;
}

void CTime::stop()
{
	status = ETime::Stop;
	this->time = 0;
}

void CTime::start()
{
	status = ETime::Run;
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


CTime::~CTime()
{
}
