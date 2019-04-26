#pragma once
#include "vector.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vector3& ori, const Vector3& dir):m_vOrigin(ori),m_vDir(dir), m_bDirNormalized(false){ }
	const Vector3& Origin() const { return m_vOrigin; }
	const Vector3& Direction() const { return m_vDir; }
	Vector3 PointAt(float parm) const { return m_vOrigin + m_vDir * parm; }
	const Vector3& NormalizedDirection() const;
private:
	Vector3 m_vOrigin;
	Vector3 m_vDir;
	Vector3 m_vNormalizedDir;
	bool m_bDirNormalized;
};

inline const Vector3& 
Ray::NormalizedDirection() const
{
	Ray* p = const_cast<Ray*>(this);
	if (p->m_bDirNormalized == false) 
	{ 
		p->m_vNormalizedDir = p->m_vDir.Normalize();
		p->m_bDirNormalized = true; 
	}
	return m_vNormalizedDir;
}
