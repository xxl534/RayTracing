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
	Vector3 InSphere();
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
	return p;
}
