#pragma once
//The Windows library is called, which has several libraries that will be used throughout the project.
#include <Windows.h>

/*
*  this class is in charge of provind a time variable that will be
*  execute in the gameloop
*/
class 
CTime{
public:
	CTime();
	~CTime();
	void 
	init();
	void 
	update();
	void 
	render();
	void 
	destroy();

private:

	//The deltatime variable is declared with which we will be calling it to occupy the time
	LARGE_INTEGER m_currentTime;
	LARGE_INTEGER m_lastTime;
	LARGE_INTEGER m_timerFrecuency;
	
public:
	float m_deltatime;
	
	
};

