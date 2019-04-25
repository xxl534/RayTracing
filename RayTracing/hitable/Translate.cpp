#include "Translate.h"

Translate::Translate(Hitable * pObj, const Vector3 & offset)
	:m_pObject(pObj)
	,m_vOffset(offset)
{
	Aabb aabb = pObj->GetAabb();
	m_aabb = Aabb(aabb.Min() + offset, aabb.Max() + offset);
}

bool Translate::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	Ray rayMoved(ray.Origin() - m_vOffset, ray.Direction());
	if (m_pObject->Hit(rayMoved, fMinCoef, fMaxCoef, rec))
	{
		rec.point += m_vOffset;
		return true;
	}
	else
	{
		return false;
	}
}
