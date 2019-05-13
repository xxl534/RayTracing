#include "Metal.h"
#include "../Random.h"
extern RandomFloat random;

Metal::Metal(const Vector3 & vAlbedo, float fuzz)
	:m_vAlbedo(vAlbedo)
	,m_fFuzz(MathClamp(fuzz, 0.f, 1.f))
{

}

Metal::~Metal()
{
}

bool 
Metal::Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	Vector3 vRefl = Vector3::Reflect(rayIn.Direction(), record.normal);
	rayScattered = Ray(record.point, vRefl);
	vAttenuation = m_vAlbedo;
	return rayScattered.Direction().dot(record.normal) > 0;
}

bool Metal::Scatter(const Ray& rayIn, const HitRecord& hitRecord, ScatterRecord& scatterRec) const
{
	scatterRec.isSpecular = true;
	Vector3 vRefl = Vector3::Reflect(rayIn.Direction(), hitRecord.normal);
	scatterRec.specularRay = Ray(hitRecord.point, vRefl + random.InSphere() * m_fFuzz);
	scatterRec.attenuation = m_vAlbedo;
	scatterRec.pdfPointer = NULL;
	return true;
}
