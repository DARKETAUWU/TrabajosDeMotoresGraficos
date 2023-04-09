#pragma once
//The Prerequisites library is called, which has several libraries that will be used throughout the project.
#include "Prerequisites.h"
//The Commons library is called, which has several libraries that will be used throughout the project.
#include "Commons.h"

//A transform class is made with which everything related to the movement of the system will be used.
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
	
	//The vector class is called with which we can adjust the vectors where the cube will move
	Vector3F Posicion3D;
	//A variable is created with which the cube will be scaled
	float m_ScaleNum;
	//A variable is created with which the cube will be rotated
	float m_RotateNum;
	//A variable is created with which a speed on the cube will be used
	float m_Speed;
};