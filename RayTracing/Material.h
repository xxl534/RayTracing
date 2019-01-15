#pragma once
#include "ray.h"
#include "Hitable.h"

class Material
{
public:
	virtual bool scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const = 0;
};