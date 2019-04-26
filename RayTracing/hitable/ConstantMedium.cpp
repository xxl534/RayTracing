#include "ConstantMedium.h"
#include "../material/Isotropic.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include "../Random.h"

extern RandomFloat random;
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

ConstantMedium::ConstantMedium(Hitable * pObj, float density, Texture * tex)
	:m_pObject(pObj)
	,m_fDensity(density)
	,m_pMaterial(new Isotropic(tex))
{

}

bool ConstantMedium::Hit(const Ray & ray, float fMinCoef, float fMaxCoef, HitRecord & rec) const
{
	HitRecord rec1, rec2;


	if (m_pObject->Hit(ray, -FLT_MAX, fMaxCoef, rec1))
	{

		Ray rayReverse(ray.Origin(), -ray.Direction());
		//if (m_pObject->Hit(rayReverse, -fMaxCoef, -rec1.coef, rec2))
		if (m_pObject->Hit(rayReverse, -FLT_MAX, -rec1.coef, rec2))
		{
			float coef0 = max(0.f, max(fMinCoef, rec1.coef));
			float coef1 = min(-rec2.coef, fMaxCoef);
			if (coef0 >= coef1)
			{
				return false;
			}
			float rayDirLen = ray.Direction().Length();
			float distanceInside = (coef1 - coef0) * rayDirLen;
			float hitDistance = -(1 / m_fDensity) * log(random.Gen());
			if (hitDistance < distanceInside)
			{
				rec.coef = coef0 + hitDistance / rayDirLen;
				rec.point = ray.PointAt(rec.coef);

				rec.normal = Vector3(1.0f, 0.0f, 0.0f);
				rec.material_ptr = m_pMaterial;
				return true;
			}
		}
	}
	return false;
}

Aabb ConstantMedium::GetAabb()
{
	return m_pObject->GetAabb();
}
