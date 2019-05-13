#pragma once
#include "../ray.h"
#include "../hitable/Hitable.h"
#include "../pdf/Pdf.h"

struct ScatterRecord
{
	Ray specularRay;
	bool isSpecular;
	Vector3 attenuation;
	Pdf* pdfPointer;
	ScatterRecord():pdfPointer(NULL),isSpecular(false){ }
	~ScatterRecord() {
		if (pdfPointer)
			delete pdfPointer;
	}
};
class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const = 0;
	virtual Vector3 Emitted(float u, float v, const Vector3& point) const { return Vector3::Zero(); }
	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, ScatterRecord& scatterRec) const { return false; }
	virtual float ScatterPdf(const Ray& rayIn, const HitRecord& record, const Ray& scattered) const { return 1.f; }
};