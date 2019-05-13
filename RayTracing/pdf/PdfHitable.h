#pragma once
#include "Pdf.h"
#include "../hitable/Hitable.h"

class PdfHitable : public Pdf
{
public:
	PdfHitable(Hitable* p, const Vector3& origin):m_pHitable(p), m_vOrigin(origin) {}
	

	virtual float Value(const Vector3& direction) const override
	{
		return m_pHitable->PdfValue(m_vOrigin, direction);
	}

	virtual Vector3 Generate() const override
	{
		return m_pHitable->Random(m_vOrigin);
	}

private:
	Vector3 m_vOrigin;
	Hitable* m_pHitable;
};