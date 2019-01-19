#pragma once
#include "Material.h"
class Dielectric :
	public Material
{
public:
	Dielectric(float ri, const Vector3& a_vAttenuation) :m_fRefractiveIndex(ri), m_vAttenuation(a_vAttenuation) {}
	~Dielectric() {}

	virtual bool Scatter(const Ray& rayIn, const HitRecord& record, Vector3& vAttenuation, Ray& rayScattered) const override;
private:
	float m_fRefractiveIndex;
	Vector3 m_vAttenuation;
};

