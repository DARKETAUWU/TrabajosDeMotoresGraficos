//The CTime library is called, which has several libraries that will be used throughout the project.
#include "CTime.h"


CTime::CTime(){
	
}

CTime::~CTime(){
}

void 
CTime::init(){
	//Retrieves the current value of the counter
	QueryPerformanceCounter(&m_lastTime);
	//Retrieves the frequency of the counter
	QueryPerformanceFrequency(&m_timerFrecuency);
}

void 
CTime::update()
{
	//Retrieves the frequency of the counter
	QueryPerformanceCounter(&m_currentTime);
	//Time is defined to pass by the lapse of time minus the last second between the computer frequency
	m_deltatime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrecuency.QuadPart;
	//the last time is equal to the time traveled
	m_lastTime = m_currentTime;
	//The time is equal to the minimum of the delta going through 0.1f
	m_deltatime = min(m_deltatime, 0.1f);
}

void 
CTime::render(){
}

void 
CTime::destroy(){
}
