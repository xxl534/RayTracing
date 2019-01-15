#pragma once
#include "Material.h"
class Metal : public Material
{
public:
	Metal(const Vector3& vAlbedo);
	~Metal();

	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;

private:
	Vector3 m_vAlbedo;
};

