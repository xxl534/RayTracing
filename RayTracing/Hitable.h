#pragma once
#include "ray.h"

class Material;
struct HitRecord
{
	float coef;
	Vector3 point;
	Vector3 normal;
	Material* material_ptr;
	HitRecord() :material_ptr(NULL) {}
};
class Hitable
{
public:
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const = 0;
};
