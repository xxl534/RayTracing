#pragma once
#include "Material.h"

class Texture;
class Isotropic : public Material
{
public: 
	Isotropic(Texture* pTex);
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const;
private:
	Texture* m_pTex;
};