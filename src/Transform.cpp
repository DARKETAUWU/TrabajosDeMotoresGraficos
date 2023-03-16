//The transfrom class is called
#include "Transform.h"

void
Transform::init() {

	// The vector x is initialized to 0
	Posicion3D.x = 0;
	// The vector y is initialized to 0
	Posicion3D.y = 0;
	// The vector z is initialized to 0
	Posicion3D.z = 0;
	//We initialize the variable m_fScaleNum giving it a value of 0.5f
	m_ScaleNum = 0.5f;
	//We initialize the variable m_fRotateNum giving it a value of 0.0002f
	m_RotateNum = 0.0002f;
	//We initialize the variable m_fSpeed ​​giving it a value of 100.0f
	m_Speed = 100.0f;
}

void
Transform::update() {
}

void
Transform::render() {
}

void
Transform::destroy() {
}