#pragma once
#include "Hitable.h"

class Translate : public Hitable
{
public: 
	Translate(Hitable* pObj, const Vector3& offset);
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
	virtual Aabb GetAabb() override { return m_aabb; }
private:
	Hitable* m_pObject;
	Vector3 m_vOffset;
	Aabb m_aabb;
};