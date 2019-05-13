#pragma once
#include "vector.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vector3& ori, const Vector3& dir):m_vOrigin(ori),m_vDir(dir.GetNormalize()){ }
	const Vector3& Origin() const { return m_vOrigin; }
	const Vector3& Direction() const { return m_vDir; }
	Vector3 PointAt(float parm) const { return m_vOrigin + m_vDir * parm; }
private:
	Vector3 m_vOrigin;
	Vector3 m_vDir;
};
