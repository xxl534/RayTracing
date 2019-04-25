#pragma once
#include "Hitable.h"
class RotateY : public Hitable
{
public:
	RotateY(Hitable* pObj, float fAngle);

	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
	virtual Aabb GetAabb() override { return m_aabb; }
private:
	Hitable* m_pObject;
	float m_fAngle;
	Aabb m_aabb;
};