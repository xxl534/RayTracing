#pragma once
#include "ray.h"
#include "Math.h"
class Camera
{
public:
	Camera(const Vector3& vAt, const Vector3& vLookAt, const Vector3& vUp, float fov, float fAspect)
	{
		Vector3 u, v, w;
		float theta = fov * kPI / 180.f;
		float halfHeight = tanf(theta / 2.f);
		float halfWidth = fAspect * halfHeight;
		m_vOrigin = vAt;
		w = (vLookAt - vAt).GetNormalize();
		u = vUp.cross(w).GetNormalize();
		v = w.cross(u);
		m_vLowerLeft = m_vOrigin - u * halfWidth - v * halfHeight + w;
		m_vHorizontal = u * 2.f * halfWidth;
		m_vVertical = v * 2.f * halfHeight;
	}
	Camera():m_vOrigin(0.f),m_vHorizontal(4.f,0.f,0.f),m_vVertical(0.f,2.f,0.f),m_vLowerLeft(-2.f,-1.f,1.f){}

	Ray	 GetRay(float u, float v) { return Ray(m_vOrigin, m_vLowerLeft + m_vHorizontal * u + m_vVertical * v - m_vOrigin); }
private:
	Vector3 m_vOrigin;
	Vector3 m_vLowerLeft;
	Vector3 m_vHorizontal;
	Vector3 m_vVertical;
};

