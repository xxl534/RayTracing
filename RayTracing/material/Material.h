#pragma once
#include "../ray.h"
#include "../hitable/Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const = 0;
	virtual Vector3 Emitted(float u, float v, const Vector3& point) const { return Vector3::Zero(); }
	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered, float& pdf) const { return false; }
	virtual float ScatterPdf(const Ray& rayIn, const HitRecord& record, const Ray& scattered) const { return 1.f; }
};