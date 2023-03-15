#pragma once
#include <Windows.h>

/*
*  this class is in charge of provind a time variable that will be
*  execute in the gameloop
*/
class CTime
{
public:
	CTime();
	~CTime();
	void init();
	void update();
	void render();
	void destroy();
	float m_deltatime;
private:
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_timerFrecuency;
	
};

