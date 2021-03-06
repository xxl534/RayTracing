#pragma once
#include "Material.h"
#include "../vector.h"
class Texture;
class Lambertian : public Material
{
public:
	Lambertian(const Vector3& albedo, Texture* pTexture);
	Lambertian(const Vector3& albedo);
	~Lambertian();

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;
	virtual float ScatterPdf(const Ray& rayIn, const HitRecord& record, const Ray& scattered) const override;
	virtual bool Scatter(const Ray& rayIn, const HitRecord& hitRecord, ScatterRecord& scatterRec) const override;
private:
	Vector3 m_vAlbedo;
	Texture* m_pTexture;
};

