#include "HitableList.h"

bool HitableList::Hit(const Ray & ray, float fMinCoef, float fMaxCoef, HitRecord & rec) const
{
	HitRecord hitRecord;
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
	return hit;
}

void HitableList::Tick(float elapsed)
{
	for (int i = 0; i < m_nSize; ++i)
	{
		m_arrHitable[i]->Tick(elapsed);
	}
}

