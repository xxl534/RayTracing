#include "Lambertian.h"
#include "../Random.h"
#include "../Texture.h"
#include "../Onb.h"
#include "../pdf/PdfCosine.h"

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
Lambertian::Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const
{
	Vector3 vRefl = record.point + record.normal + random.InSphere();
	rayScattered = Ray(record.point, vRefl - record.point);
	vAttenuation = m_pTexture ? m_vAlbedo * m_pTexture->Sample(0, 0, record.point) : m_vAlbedo;
	return true;
}

bool Lambertian::Scatter(const Ray& rayIn, const HitRecord& hitRecord, ScatterRecord& scatterRec) const
{
	scatterRec.isSpecular = false;
	scatterRec.attenuation = m_pTexture ? m_vAlbedo * m_pTexture->Sample(0, 0, hitRecord.point) : m_vAlbedo;
	scatterRec.pdfPointer = new PdfCosine(hitRecord.normal);
	return true;
}

float Lambertian::ScatterPdf(const Ray& rayIn, const HitRecord& record, const Ray& scattered) const
{
	float cos = record.normal.dot(scattered.Direction().GetNormalize());
	if (cos < 0.f)
	{
		cos = 0.f;
	}
	return cos / kPI;
}
