#pragma once
#include "Aabb.h"
#include "Hitable.h"

struct BvhNodeBase;
class Hitable;
struct BVH
{
	BVH( Hitable** objList, int count );
	Aabb GetAabb() const { return m_pRoot->GetAabb(); }
	bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec);
	~BVH();
private:
	Hitable* m_pRoot;
};

class BvhBranchNode : public Hitable
{
public:
	BvhBranchNode(Hitable** arrLeaf, int count, const Aabb& aabb);
	virtual ~BvhBranchNode() { delete m_pLeft; delete m_pRight; }
	virtual bool Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const override;
	virtual Aabb GetAabb() override;
private:
	Hitable* m_pLeft;
	Hitable* m_pRight;
	Aabb m_aabb;
};