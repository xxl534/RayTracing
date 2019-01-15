#include "Lambertian.h"
#include "Random.h"
extern RandomFloat random;
Lambertian::Lambertian(const Vector3& albedo)
	:m_vAlbedo(albedo)
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
	vAttenuation = m_vAlbedo;
	return true;
}
