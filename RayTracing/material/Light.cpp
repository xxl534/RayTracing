#include "Light.h"
#include "../Texture.h"
//////////////////////////////////////////////////////////////////////////
//DiffuseLight
//////////////////////////////////////////////////////////////////////////
DiffuseLight::DiffuseLight(Texture* pTex)
	:m_pTex(pTex)
{

}

bool DiffuseLight::Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(float u, float v, const Vector3& point) const
{
	return m_pTex->Sample(u, v, point);
}

