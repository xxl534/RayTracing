#pragma once
#include "Pdf.h"
#include "../Onb.h"
#include "../Random.h"

extern RandomFloat random;
class PdfCosine : public Pdf
{
public:
	PdfCosine(const Vector3& normal):m_onb(normal){}
	virtual float Value(const Vector3& direction) const override
	{
		float cosine = direction.dot(m_onb.W());
		return cosine > 0.f ? cosine / kPI : 0.f;
	}

	virtual Vector3 Generate() const override
	{
		return m_onb.Local(random.CosineDirection());
	}
private:
	Onb m_onb;
};