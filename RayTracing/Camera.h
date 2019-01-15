#pragma once
#include "ray.h"
#include "Math.h"
#include "Random.h"
extern RandomFloat random;
inline Vector3 RandomInUnitDisk()
{
	Vector3 p;
	do 
	{
		p = Vector3(random.Gen(), random.Gen(), 0.f) *2.f - Vector3(1.f, 1.f, 0.f);
	} while ( p.LengthSqr() >= 1.f);
	return p;
}
class Camera
{
public:
	Camera(const Vector3& vAt, const Vector3& vLookAt, const Vector3& vUp, float fov, float fAspect, float aperture, float focusDist)
	{
		m_fLensRadius = aperture / 2.f;
		float theta = fov * kPI / 180.f;
		float halfHeight = tanf(theta / 2.f);
		float halfWidth = fAspect * halfHeight;
		m_vOrigin = vAt;
		m_w = (vLookAt - vAt).GetNormalize();
		m_u = vUp.cross(m_w).GetNormalize();
		m_v = m_w.cross(m_u);
		m_vLowerLeft = m_vOrigin + ( - m_u * halfWidth - m_v * halfHeight + m_w ) * focusDist;
		m_vHorizontal = m_u * 2.f * halfWidth * focusDist;
		m_vVertical = m_v * 2.f * halfHeight * focusDist;
	}

	Ray	 GetRay(float s, float t) 
	{ 
		Vector3 rd = RandomInUnitDisk() * m_fLensRadius;
		Vector3 offset = m_u * rd.x + m_v * rd.y;
		return Ray(m_vOrigin + offset, m_vLowerLeft + m_vHorizontal * s + m_vVertical * t - m_vOrigin - offset ); 
	}
private:
	Vector3 m_vOrigin;
	Vector3 m_vLowerLeft;
	Vector3 m_vHorizontal;
	Vector3 m_vVertical;
	Vector3 m_u, m_v, m_w;
	float m_fLensRadius;
};

