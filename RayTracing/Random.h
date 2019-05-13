#pragma once
#include <random>
#include <functional>
#include "vector.h"
class RandomFloat
{
public:
	RandomFloat() :m_distribution(0.f,1.f),m_dice(m_distribution, m_generator){
		//m_dice = std::bind(m_distribution, m_generator);
	}
	float Gen() { return m_dice(); }
	float Gen(float min, float max) { return Gen() * (max - min) + min; }
	Vector3 InSphere();
	Vector3 CosineDirection();
private:
	std::default_random_engine m_generator;
	std::uniform_real_distribution<float> m_distribution;
	std::_Binder<std::_Unforced, std::uniform_real_distribution<float>&, std::default_random_engine&> m_dice;
};
inline Vector3 
RandomFloat::InSphere()
{
	Vector3 p;
	do 
	{
		p = Vector3(Gen(), Gen(), Gen()) *2.f - Vector3(1.f);
	} while (p.LengthSqr() >= 1.f);
	return p.GetNormalize();
}

inline Vector3
RandomFloat::CosineDirection()
{
	Vector3 p;
	float r1 = Gen();
	float r2 = Gen();
	float cosTheta = sqrt(1 - r2);
	float sinTheta = sqrt(r2);
	float phi = 2 * kPI * r1;
	float z = cosTheta;
	float x = cos(phi) * sinTheta;
	float y = sin(phi) * sinTheta;
	return Vector3(x, y, z);
}