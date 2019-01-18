#include "BVH.h"
#include <assert.h>
#include "Hitable.h"

Hitable* _GeneNode(Hitable** arrLeaf, int count,const Aabb& aabb)
{
	assert(count > 0);
	
	if (count > 1)
	{
		return new BvhBranchNode(arrLeaf, count, aabb);
	}
	else
	{
		return arrLeaf[0];
	}
}

BVH::BVH(Hitable** objList, int count)
	:m_pRoot(NULL)
{
	Aabb aabbSum;
	for (int i = 0; i < count; ++i)
	{
		aabbSum = Aabb::Merge(aabbSum, objList[i]->GetAabb());
	}
	m_pRoot = _GeneNode(objList, count, aabbSum);
}

bool BVH::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec)
{
	return m_pRoot->Hit(ray, fMinCoef, fMaxCoef, rec);
}

BVH::~BVH()
{
	delete m_pRoot;
}

//////////////////////////////////////////////////////////////////////////
int _CmpAabbX(const void* a,const void* b)
{
	Hitable* pA = *((Hitable**)a);
	Hitable* pB = *((Hitable**)b);
	const Vector3& vMaxA = pA->GetAabb().Max();
	const Vector3& vMaxB = pB->GetAabb().Max();
	if (vMaxA.x == vMaxB.x)
	{
		const Vector3& vMinA = pA->GetAabb().Min();
		const Vector3& vMinB = pB->GetAabb().Min();
		if (vMinA.x == vMinB.x)
		{
			return 0;
		}
		else
		{
			return vMinA.x < vMinB.x ? -1 : 1;
		}
	}
	else
	{
		return vMaxA.x < vMaxB.x ? -1 : 1;
	}
}
int _CmpAabbY(const void* a,const void* b)
{
	Hitable* pA = *((Hitable**)a);
	Hitable* pB = *((Hitable**)b);
	const Vector3& vMaxA = pA->GetAabb().Max();
	const Vector3& vMaxB = pB->GetAabb().Max();
	if (vMaxA.y == vMaxB.y)
	{
		const Vector3& vMinA = pA->GetAabb().Min();
		const Vector3& vMinB = pB->GetAabb().Min();
		if (vMinA.y == vMinB.y)
		{
			return 0;
		}
		else
		{
			return vMinA.y < vMinB.y ? -1 : 1;
		}
	}
	else
	{
		return vMaxA.y < vMaxB.y ? -1 : 1;
	}
}
int _CmpAabbZ(const void* a,const void* b)
{

	Hitable* pA = *((Hitable**)a);
	Hitable* pB = *((Hitable**)b);
	const Vector3& vMaxA = pA->GetAabb().Max();
	const Vector3& vMaxB = pB->GetAabb().Max();
	if (vMaxA.z == vMaxB.z)
	{
		const Vector3& vMinA = pA->GetAabb().Min();
		const Vector3& vMinB = pB->GetAabb().Min();
		if (vMinA.z == vMinB.z)
		{
			return 0;
		}
		else
		{
			return vMinA.z < vMinB.z ? -1 : 1;
		}
	}
	else
	{
		return vMaxA.z < vMaxB.z ? -1 : 1;
	}
}

typedef int(*AabbCmpFunc)(const void* a,const void* b);
AabbCmpFunc cmps[] = {
	_CmpAabbX, _CmpAabbY, _CmpAabbZ
};
BvhBranchNode::BvhBranchNode(Hitable** arrLeaf, int count, const Aabb& aabb)
	:m_aabb(aabb)
	,m_pLeft(NULL)
	,m_pRight(NULL)
{
	assert(count >= 2);
	Vector3 vDiag = m_aabb.Max() - m_aabb.Min();
	float fBiaDiag = 0.f;
	int offset = -1;
	for (int i = 0; i < 3; ++i)
	{
		if (vDiag.f[i] > fBiaDiag)
		{
			fBiaDiag = vDiag.f[i];
			offset = i;
		}
	}
	assert(offset >= 0 && offset < 3);
	qsort(arrLeaf, count, sizeof(Hitable*), cmps[offset]);
	int l = 0, r = count - 1;
	Aabb aabbL = arrLeaf[l]->GetAabb();
	Aabb aabbR = arrLeaf[r]->GetAabb();
	while (r - l > 1)
	{
		Hitable* pLeafL = arrLeaf[l + 1];
		Aabb aabbNewL = Aabb::Merge(aabbL, pLeafL->GetAabb());
		float fVolumeDeltaL = aabbNewL.Volume() - aabbL.Volume();
		Hitable* pLeafR = arrLeaf[r - 1];
		Aabb aabbNewR = Aabb::Merge(aabbR, pLeafR->GetAabb());
		float fVolumeDeltaR = aabbNewR.Volume() - aabbR.Volume();
		if (fVolumeDeltaL < fVolumeDeltaR)
		{
			++l;
			aabbL = aabbNewL;
		}
		else
		{
			--r;
			aabbR = aabbNewR;
		}
	}
	m_pLeft = _GeneNode(arrLeaf, r, aabbL);
	m_pRight = _GeneNode(arrLeaf + r, count - r, aabbR);
}

bool BvhBranchNode::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	Hitable* p0 = m_pLeft;
	Hitable* p1 = m_pRight;
	float fMin0, fMin1;
	bool bHit0 = p0->GetAabb().Hit(ray, fMinCoef, fMaxCoef, fMin0);
	bool bHit1 = p1->GetAabb().Hit(ray, fMinCoef, fMaxCoef, fMin1);
	if (bHit0 && bHit1)
	{
		if ( fMin1 < fMin0 )
		{
			MathSwap(p0, p1);
			MathSwap(fMin0, fMin1);
		}
		HitRecord hr0; 
		HitRecord hr1;
		if (p0->Hit(ray, fMinCoef, fMaxCoef, hr0))
		{
			if (hr0.coef > fMin1 && p1->Hit(ray, fMinCoef, fMaxCoef, hr1) && (hr1.coef < hr0.coef))
			{
				rec = hr1;
			}
			else
			{
				rec = hr0;
			}
			return true;
		}
		else
		{
			return p1->Hit(ray, fMinCoef, fMaxCoef, rec);
		}
	}
	if (bHit0)
	{
		return p0->Hit(ray, fMinCoef, fMaxCoef, rec);
	}
	if (bHit1)
	{
		return p1->Hit(ray, fMinCoef, fMaxCoef, rec);
	}
	return false;
}

Aabb BvhBranchNode::GetAabb()
{
	return m_aabb;
}
