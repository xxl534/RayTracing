#pragma once
#include "vector.h"
class Texture
{
public:
	virtual Vector3 Sample(float u, float v, const Vector3& point) const = 0;
};

class ConstantTexture : public Texture
{
public:
	ConstantTexture(const Vector3& color ): m_color(color){}

	virtual Vector3 Sample(float u, float v, const Vector3& point) const override
	{
		return m_color;
	}
private:
	Vector3 m_color;
};

class CheckerTexture : public Texture
{
public:
	CheckerTexture(Texture* pOdd, Texture* pEven) :m_pOdd(pOdd), m_pEven(pEven) {}
	virtual Vector3 Sample(float u, float v, const Vector3& point) const override
	{
		float sine = MathSinFloat(point.x*3.f) * MathSinFloat(point.y*3.f) * MathSinFloat(point.z*3.f);
		return sine < 0 ? m_pOdd->Sample(u, v, point) : m_pEven->Sample(u, v, point);
	}
private:
	Texture* m_pOdd;
	Texture* m_pEven;
};