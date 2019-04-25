#pragma once
#include "Hitable.h"
class Material;
class Quad : public Hitable
{
public:
	Quad(const Vector3& pos, const Vector3& normal, const Vector3& up, float width, float height, Material* pMat);
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;

	virtual Aabb GetAabb() override;
private:
	Aabb m_aabb;
	Vector3 m_position;
	Vector3 m_normal;
	Vector3 m_up;
	Vector3 m_right;
	float m_width, m_height;
	Material* m_pMaterial;
};