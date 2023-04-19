//The transfrom class is called
#include "Transform.h"

void
Transform::init() {
	m_ScaleNum = 0.5f;
	m_RotateNum = 0.0002f;
	m_Speed = 100.0f;

	m_v3Scale.x = 0.5f;
	m_v3Scale.y = 0.5f;
	m_v3Scale.z = 0.5f;
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