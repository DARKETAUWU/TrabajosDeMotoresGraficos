#include "Time.h"



Time::Time()
{
	
}

Time::~Time()
{
}

void Time::init()
{
	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceFrequency(&m_timerFrecuency);
}

void Time::update()
{
	QueryPerformanceCounter(&m_currentTime);
	m_deltatime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrecuency.QuadPart;
	m_lastTime = m_currentTime;
	m_deltatime = min(m_deltatime, 0.1f);
}

void Time::render()
{
}

void Time::destroy()
{
}
