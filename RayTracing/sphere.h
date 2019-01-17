#pragma once
#include "vector.h"
#include "ray.h"
#include "Hitable.h"
class Sphere : public Hitable
{
public:
	Sphere(const Vector3& vCenter, float fRadius, Material* pMat) :m_vOrigin(vCenter), m_fRadius(fRadius), m_pMaterial(pMat), m_vVelocity(0.f),m_vAcceleration(0.f) {}
	Sphere(const Vector3& vCenter, const Vector3& vVelocity, const Vector3& vAcceleration, float fRadius, Material* pMat) 
		:m_vOrigin(vCenter), m_fRadius(fRadius), m_pMaterial(pMat), m_vVelocity( vVelocity), m_vAcceleration(vAcceleration) {}
	const Vector3& Center() const {return m_vCenter;}
	float Radius() const { return m_fRadius; }

	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
	virtual void UpdateStateAtTime(float elapsed) override;
private:
	Vector3 m_vCenter;
	Vector3 m_vOrigin;
	Vector3 m_vVelocity;
	Vector3 m_vAcceleration;
	float m_fRadius;
	Material* m_pMaterial;
};

