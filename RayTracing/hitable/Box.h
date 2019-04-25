#pragma once
#include "Hitable.h"

class Box : public Hitable
{
public:
	Box(const Vector3& size, Material* pMat);
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
	virtual Aabb GetAabb() override { return m_aabb; }
private:
	Hitable* m_arrPlane[6];
	Aabb m_aabb;
};