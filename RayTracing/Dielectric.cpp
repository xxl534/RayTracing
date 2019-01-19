#include "Dielectric.h"
#include "RTMath.h"
#include "Random.h"
extern RandomFloat random;
inline float Pow5(float f)
{
	float f2 = f * f;
	return f2 * f2 * f;
}
inline float SchlickReflectivity(float cosine, float refractiveIndex)
{
	float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0)* Pow5(1 - cosine);
}
bool Dielectric::scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	Vector3 vOutwardNormal;
	float fRefractiveRadio;
	vAttenuation = m_vAttenuation;
	bool bIntoAir = rayIn.Direction().dot(record.normal) > 0;
	if ( bIntoAir )
	{//to air
		vOutwardNormal = -record.normal;
		fRefractiveRadio = m_fRefractiveIndex;
	}
	else
	{//into material
		vOutwardNormal = record.normal;
		fRefractiveRadio = 1.f / m_fRefractiveIndex;
	}

	Vector3 vRefracted;
	float fReflectProb;
	if (Vector3::Refract(rayIn.NormalizedDirection(), vOutwardNormal, fRefractiveRadio, vRefracted))
	{
		float cosine;
		if (bIntoAir)
		{
			//cosine = sqrtf(1 - Square(-(vOutwardNormal.dot(rayIn.NormalizedDirection())) * m_fRefractiveIndex));
			cosine = -(vOutwardNormal.dot(rayIn.NormalizedDirection())) * m_fRefractiveIndex;
		}
		else
		{
			cosine = -(vOutwardNormal.dot(rayIn.NormalizedDirection()));
		}
		fReflectProb = SchlickReflectivity(cosine, m_fRefractiveIndex);
	}
	else
	{
		fReflectProb = 1.f;
	}
	if (random.Gen() < fReflectProb)
	{
		Vector3 vReflected = Vector3::Reflect(rayIn.Direction(), record.normal);
		rayScattered = Ray(record.point, vReflected);
	}
	else
	{
		rayScattered = Ray(record.point, vRefracted);
	}
	return true;
}
