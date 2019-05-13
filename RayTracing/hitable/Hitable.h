#pragma once
#include "../ray.h"
#include "../Aabb.h"
class Material;
struct HitRecord
{
	float coef;
	Vector3 point;
	Vector3 normal;
	float u, v;
	Material* material_ptr;
	HitRecord() :material_ptr(NULL) {}
};
class Hitable
{
public:
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const = 0;
	virtual Aabb GetAabb() = 0;
	virtual float PdfValue(const Vector3& origin, const Vector3 direction) const { return 0.f; }
	virtual Vector3 Random(const Vector3& origin) const { return Vector3(1.f, 0.f, 0.f); }
};

