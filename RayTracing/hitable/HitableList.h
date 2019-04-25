#pragma once
#include "Hitable.h"
struct BVH;
class HitableList : 
	public Hitable
{
public:
	HitableList(Hitable** arrHitable, int nSize);
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const;
	virtual Aabb GetAabb() override;
private:
	BVH* m_bvh;
	Hitable** m_arrHitable;
	int m_nSize;
};

