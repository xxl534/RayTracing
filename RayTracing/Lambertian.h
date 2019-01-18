#pragma once
#include "Material.h"
#include "vector.h"
class Texture;
class Lambertian : public Material
{
public:
	Lambertian(const Vector3& albedo, Texture* pTexture);
	Lambertian(const Vector3& albedo);
	~Lambertian();

	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;

private:
	Vector3 m_vAlbedo;
	Texture* m_pTexture;
};

