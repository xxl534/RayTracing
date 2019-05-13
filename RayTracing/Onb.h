#pragma once
#include "vector.h"
class Onb
{
public:
	Onb(const Vector3& vec) {
		m_axis[2] = vec.GetNormalize();
		Vector3 a(m_axis[2].y, m_axis[2].z, m_axis[2].x);
		m_axis[0] = a.cross(m_axis[2]);
		m_axis[1] = m_axis[2].cross(m_axis[0]);
	}
	Vector3 U() const { return m_axis[0]; }
	Vector3 V() const { return m_axis[1]; }
	Vector3 W() const { return m_axis[2]; }
	Vector3 Local(float x, float y, float z) const { return m_axis[0] * x + m_axis[1] * y + m_axis[2] * z; }
	Vector3 Local(const Vector3& vec) const { return m_axis[0] * vec.x + m_axis[1] * vec.y + m_axis[2] * vec.z; }
private:
	Vector3 m_axis[3];
};