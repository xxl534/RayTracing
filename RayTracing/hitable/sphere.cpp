#include "Sphere.h"
#include "../RTMath.h"

extern float gElapsed;
extern float gShutterDuration;
Sphere::Sphere(const Vector3& vCenter, float fRadius, Material* pMat) :m_vOrigin(vCenter), m_fRadius(fRadius), m_pMaterial(pMat), m_vVelocity(0.f), m_vAcceleration(0.f)
{
	_InitAabb();
}

Sphere::Sphere(const Vector3& vCenter, const Vector3& vVelocity, const Vector3& vAcceleration, float fRadius, Material* pMat) : m_vOrigin(vCenter), m_fRadius(fRadius), m_pMaterial(pMat), m_vVelocity(vVelocity), m_vAcceleration(vAcceleration)
{
	_InitAabb();
}

Vector3 Sphere::Center() const
{
	return m_vOrigin + m_vVelocity * gElapsed + m_vAcceleration * (0.5f * gElapsed * gElapsed);
}

bool Sphere::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	Vector3 vCenter = Center();
	Vector3 oc = ray.Origin() - vCenter;
	float a = ray.Direction().LengthSqr();
	float b = oc.dot(ray.Direction()) * 2.f;
	float c = oc.LengthSqr() - Radius() * Radius();
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
	{
		float fDiscriminantSqrt = sqrt(discriminant);
		float fCoef = (-b - fDiscriminantSqrt) / (2 * a);
		if (fCoef <= fMinCoef || fCoef >= fMaxCoef)
		{
			fCoef = (-b + fDiscriminantSqrt) / (2 * a);
		}
		if (fCoef > fMinCoef && fCoef < fMaxCoef)
		{
			rec.coef = fCoef;
			rec.u = 0.f;
			rec.v = 0.f;
			rec.point = ray.PointAt(rec.coef);
			rec.normal = (rec.point - vCenter)/ Radius();
			rec.material_ptr = m_pMaterial;
			return true;
		}
	}
	return false;
}

Aabb Sphere::GetAabb()
{
	return m_aabb;
}

void Sphere::_InitAabb()
{
	Vector3 vMin, vMax;
	for (int offset = 0; offset < 3; ++offset)
	{
		float fVelo = m_vVelocity.f[offset];
		float fAccel = m_vAcceleration.f[offset];
		float fTransStart = 0.f, fTransMid = 0.f, fTransEnd = fVelo * gShutterDuration + fAccel * (gShutterDuration *gShutterDuration) * 0.5f;
		if (fVelo * fAccel < 0)
		{//速度和加速度反方向
			float t = -fVelo / fAccel; //速度为0的时间;
			if (t > 0 && t < gShutterDuration)
			{
				fTransMid = fVelo * t + fAccel * (t *t) * 0.5f;
			}
		}
		float fTransMin = Min(fTransStart, Min(fTransMid, fTransEnd));
		float fTransMax = Max(fTransStart, Max(fTransMid, fTransEnd));
		vMin.f[offset] = m_vOrigin.f[offset] + fTransMin - m_fRadius;
		vMax.f[offset] = m_vOrigin.f[offset] + fTransMax + m_fRadius;
	}
	m_aabb = Aabb(vMin, vMax);
}
