#include "Box.h"
#include "Quad.h"
static Vector3 s_boxCenter[6] = {
	Vector3(-0.5f,0.f,0.f),Vector3(0.5f,0.f,0.f), Vector3(0.f, -0.5f,0.f), Vector3(0.f,0.5f,0.f), Vector3(0.f,0.f,-0.5f),Vector3(0.f,0.f,0.5f) 
};
static Vector3 s_boxNormal[6] = {
	Vector3(-1.f,0.f,0.f),Vector3(1.f,0.f,0.f),Vector3(0.f,-1.f,0.f),Vector3(0.f,1.f,0.f),Vector3(0.f,0.f,-1.f),Vector3(0.f,0.f,1.f)
};
static Vector3 s_boxUp[6] = {
	Vector3(0.f,1.f,0.f),Vector3(0.f,1.f,0.f),Vector3(0.f,0.f,-1.f),Vector3(0.f,0.f,1.f),Vector3(0.f,1.f,0.f),Vector3(0.f,1.f,0.f),
};
static int s_sizeOffset[6] = {
 0,0,1,1,2,2
};
static int s_sizeWidth[6] = {
	2,2,0,0,0,0
};
static int s_sizeHeight[6] = {
	1,1,2,2,1,1
};
Box::Box(const Vector3& size,Material* pMat)
{
	Vector3 vCenterArr[6];
	for (int i = 0; i < 6; ++i)
	{
		Vector3 vCenter = s_boxCenter[i];

		vCenter *= size.f[s_sizeOffset[i]];
		float width = size.f[s_sizeWidth[i]];
		float height = size.f[s_sizeHeight[i]];
		Vector3 vNormal = s_boxNormal[i];
		Vector3 vUp = s_boxUp[i];
		m_arrPlane[i] = new Quad(vCenter, vNormal, vUp, width, height, pMat);
		m_aabb = Aabb::Merge(m_aabb, m_arrPlane[i]->GetAabb());
	}
}

bool Box::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	for (int i = 0; i < 6; ++i)
	{
		if (m_arrPlane[i]->Hit(ray, fMinCoef, fMaxCoef, rec))
		{
			return true;
		}
	}
	return false;
	//return m_arrPlane[4]->Hit(ray, fMinCoef, fMaxCoef, rec);
}
