#include "Rotate.h"

RotateY::RotateY(Hitable* pObj, float fAngle)
	:m_pObject(pObj)
	,m_fAngle(fAngle)
{
	Aabb aabb = pObj->GetAabb();
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				float x = aabb.Max().x * i + aabb.Min().x * (1 - i);
				float y = aabb.Max().y * j + aabb.Min().y * (1 - j);
				float z = aabb.Max().z * k + aabb.Min().z * (1 - k);
				Vector3 v(x, y, z);
				v.RotateXZBy(fAngle);
				m_aabb.MergePoint(v);
			}
		}
	}
}

bool RotateY::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	Vector3 vNewOri = ray.Origin();
	vNewOri.RotateXZBy(-m_fAngle);
	Vector3 vNewDir = ray.Direction();
	vNewDir.RotateXZBy(-m_fAngle);
	Ray rayNew(vNewOri, vNewDir);
	if (m_pObject->Hit(rayNew, fMinCoef, fMaxCoef, rec))
	{
		rec.point.RotateXZBy(m_fAngle);
		rec.normal.RotateXZBy(m_fAngle);
		return true;
	}
	else
	{
		return false;
	}
}


