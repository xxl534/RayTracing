#pragma once
#include "vector.h"
#include "Math.h"
#include "Ray.h"

struct Aabb
{
	Aabb();
	Aabb(const Vector3& min, const Vector3& max);
	bool FitIn(const Aabb& a);
	static Aabb Merge(const Aabb& a, const Aabb& b);
	const Vector3& Max() const { return m_vMax; }
	const Vector3& Min() const { return m_vMin; }
	float Volume() const;
	bool Hit(const Ray& ray, float tMin, float tMax, float& outMin) const;
private:
	Vector3 m_vMin;
	Vector3 m_vMax;
};

inline Aabb::Aabb()
	:m_vMin(10000.f)
	,m_vMax(-10000.f)
{

}

inline Aabb::Aabb(const Vector3& min, const Vector3& max)
	:m_vMin(min)
	,m_vMax(max)
{

}

inline bool 
Aabb::FitIn(const Aabb& a)
{
	return a.m_vMin >= m_vMin && a.m_vMax <= m_vMax;
}

inline Aabb 
Aabb::Merge(const Aabb& a, const Aabb& b)
{
	return Aabb(Vector3::MergeMin(a.m_vMin, b.m_vMin), Vector3::MergeMax(a.m_vMax, b.m_vMax));
}

inline float Aabb::Volume() const
{
	Vector3 vDiag = m_vMax - m_vMin;
	return vDiag.x * vDiag.y * vDiag.z;
}

inline bool Aabb::Hit(const Ray& ray, float tMin, float tMax, float& outMin) const
{
	for (int offset = 0; offset < 3; ++offset)
	{
		const Vector3& vDir = ray.Direction();
		if (!MathNearlyZero(vDir.f[offset]))
		{
			float fRecip = 1.f / vDir.f[offset];
			float t0 = (m_vMin.f[offset] - ray.Origin().f[offset]) * fRecip;
			float t1 = (m_vMax.f[offset] - ray.Origin().f[offset]) * fRecip;
			if (fRecip < 0.f)
			{
				MathSwap(t0, t1);
			}
			tMin = t0 > tMin ? t0 : tMin;
			tMax = t1 < tMax ? t1 : tMax;
			if (tMax <= tMin)
			{
				return false;
			}
		}
		else
		{
			if (ray.Origin().f[offset] < m_vMin.f[offset] || ray.Origin().f[offset] > m_vMax.f[offset])
			{
				return false;
			}
		}
	}
	outMin = tMin;
	return true;
}
