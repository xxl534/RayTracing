#pragma once
#include "ray.h"
#include "Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const = 0;
	virtual Vector3 Emitted(float u, float v, const Vector3& point) const { return Vector3::Zero(); }
};