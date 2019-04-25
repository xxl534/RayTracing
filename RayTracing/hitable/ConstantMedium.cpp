#include "ConstantMedium.h"

ConstantMedium::ConstantMedium(Hitable * pObj, float density, Texture * tex)
{

}

bool ConstantMedium::Hit(const Ray & ray, float fMinCoef, float fMaxCoef, HitRecord & rec)
{
	return false;
}

Aabb ConstantMedium::GetAabb()
{
	return Aabb();
}
