#include "Metal.h"


Metal::Metal(const Vector3 & vAlbedo)
	:m_vAlbedo(vAlbedo)
{
}

Metal::~Metal()
{
}

bool 
Metal::scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	Vector3 vRefl = Vector3::Reflect(rayIn.Direction(), record.normal);
	rayScattered = Ray(record.point, vRefl);
	vAttenuation = m_vAlbedo;
	return rayScattered.Direction().dot(record.normal) > 0;
}
