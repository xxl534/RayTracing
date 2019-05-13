#pragma once
#include "Material.h"
class Metal : public Material
{
public:
	Metal(const Vector3& vAlbedo, float fuzz = 0.f);
	~Metal();

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;
	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, ScatterRecord& scatterRec) const override;

private:
	Vector3 m_vAlbedo;
	float m_fFuzz;
};

