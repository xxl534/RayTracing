#pragma once
#include "Hitable.h"
class HitableList : 
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** arrHitable, int nSize) :m_arrHitable(arrHitable), m_nSize(nSize) {}
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const;
private:
	Hitable** m_arrHitable;
	int m_nSize;
};

