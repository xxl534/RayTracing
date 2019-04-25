#pragma once
#include "../vector.h"
#include "../ray.h"
#include "Hitable.h"
class Sphere : public Hitable
{
public:
	Sphere(const Vector3& vCenter, float fRadius, Material* pMat);
	Sphere(const Vector3& vCenter, const Vector3& vVelocity, const Vector3& vAcceleration, float fRadius, Material* pMat);
	Vector3 Center() const;
	float Radius() const { return m_fRadius; }

	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;

	virtual Aabb GetAabb() override;
private:
	void _InitAabb();
private:
	Vector3 m_vOrigin;
	Vector3 m_vVelocity;
	Vector3 m_vAcceleration;
	float m_fRadius;
	Material* m_pMaterial;
	Aabb m_aabb;
};

