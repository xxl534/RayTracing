#include "HitableList.h"
#include "../BVH.h"
HitableList::HitableList(Hitable** arrHitable, int nSize) :m_arrHitable(arrHitable), m_nSize(nSize),m_bvh(NULL)
{
	m_bvh = new BVH(arrHitable, nSize);
}

bool HitableList::Hit(const Ray & ray, float fMinCoef, float fMaxCoef, HitRecord & rec) const
{
	return m_bvh->Hit(ray, fMinCoef, fMaxCoef, rec);
	/*HitRecord hitRecord;
	bool hit = false;
	float closest = fMaxCoef;
	for (int i = 0; i < m_nSize; ++i )
	{
		if (m_arrHitable[i]->Hit(ray, fMinCoef, closest, hitRecord))
		{
			hit = true;
			closest = hitRecord.coef;
			rec = hitRecord;
		}
	}
	return hit;*/
}

Aabb HitableList::GetAabb()
{
	return m_bvh->GetAabb();
}

