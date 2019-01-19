#pragma once
#include "Material.h"
class Texture;
class DiffuseLight : public Material
{
public:
	DiffuseLight(Texture* pTex);
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;
	virtual Vector3 Emitted(float u, float v, const Vector3& point) const override;
private:
	Texture* m_pTex;
};