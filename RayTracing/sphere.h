#pragma once
#include "vector.h"
#include "ray.h"
#include "Hitable.h"
class Sphere : public Hitable
{
public:
	~Sphere();
	Sphere(const Vector3& vCenter, float fRadius, Material* pMat) :m_vCenter(vCenter), m_fRadius(fRadius), m_pMaterial(pMat) {}
	const Vector3& Center() const {return m_vCenter;}
	float Radius() const { return m_fRadius; }

	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
private:
	Vector3 m_vCenter;
	float m_fRadius;
	Material* m_pMaterial;
};

