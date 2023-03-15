#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"
#include "Commons.h"

class Transform {
public:
	Transform() = default;
	~Transform() {};

	void
		init();
	void
		update();
	void
		render();
	void
		destroy();
public:
	
	Vector3 Posicion3D;
	float m_fScaleNum;
	float m_fRotateNum;
	float m_fSpeed;
};