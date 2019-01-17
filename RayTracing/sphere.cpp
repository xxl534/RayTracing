#include "Sphere.h"

bool Sphere::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	Vector3 oc = ray.Origin() - Center();
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
			rec.point = ray.PointAt(rec.coef);
			rec.normal = (rec.point - Center() )/ Radius();
			rec.material_ptr = m_pMaterial;
			return true;
		}
	}
	return false;
	
}

void Sphere::UpdateStateAtTime(float elapsed)
{
	m_vCenter = m_vOrigin + m_vVelocity * elapsed + m_vAcceleration * (0.5f * elapsed * elapsed);
}
