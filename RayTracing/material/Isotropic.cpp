#include "Isotropic.h"
#include "../Random.h"
#include "../Texture.h"

extern RandomFloat random;
Isotropic::Isotropic(Texture * pTex)
	:m_pTex(pTex)
{
}

bool Isotropic::Scatter(const Ray & rayIn, const HitRecord & record, Vector3 & vAttenuation, Ray & rayScattered) const
{
	rayScattered = Ray(record.point, random.InSphere());
	vAttenuation = m_pTex->Sample(record.u, record.v, record.point);
	return true;
}
