#include "Lambertian.h"
#include "Random.h"
#include "Texture.h"
extern RandomFloat random;
Lambertian::Lambertian(const Vector3 & albedo, Texture * pTexture)
	:m_vAlbedo(albedo)
	,m_pTexture(pTexture)
{
}
Lambertian::Lambertian(const Vector3& albedo)
	:m_vAlbedo(albedo)
	,m_pTexture(NULL)
{
}

Lambertian::~Lambertian()
{
}

bool 
Lambertian::scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	Vector3 vRefl = record.point + record.normal + random.InSphere();
	rayScattered = Ray(record.point, vRefl - record.point);
	vAttenuation = m_pTexture ? m_vAlbedo * m_pTexture->Sample(0, 0, record.point) : m_vAlbedo;
	return true;
}
