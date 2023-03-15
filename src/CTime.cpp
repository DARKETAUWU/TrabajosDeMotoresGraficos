#include "CTime.h"



CTime::CTime()
{
	
}

CTime::~CTime()
{
}

void CTime::init()
{
	QueryPerformanceCounter(&m_lastTime);
	QueryPerformanceFrequency(&m_timerFrecuency);
}

void CTime::update()
{
	QueryPerformanceCounter(&m_currentTime);
	m_deltatime = (m_currentTime.QuadPart - m_lastTime.QuadPart) / (float)m_timerFrecuency.QuadPart;
	m_lastTime = m_currentTime;
	m_deltatime = min(m_deltatime, 0.1f);
}

void CTime::render()
{
}

void CTime::destroy()
{
}
