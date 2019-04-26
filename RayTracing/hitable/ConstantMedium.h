#pragma once
#include "Hitable.h"

class Texture;
class ConstantMedium : public Hitable
{
public:
	ConstantMedium(Hitable* pObj, float density, Texture* tex);
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const;
	virtual Aabb GetAabb();
private:
	Hitable* m_pObject;
	float m_fDensity;
	Material* m_pMaterial;
};