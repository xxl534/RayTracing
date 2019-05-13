#include "Pdf.h"
#include <memory.h>
#include <assert.h>
#include "../Random.h"
extern RandomFloat random;
class PdfMixture : public Pdf
{
public:
	PdfMixture(int len):m_len(len) {
		assert(len > 0);
		m_weight = 1.f / len;
		m_arrPdfs = new Pdf*[len]; 
		memset(m_arrPdfs, 0, sizeof(Pdf*) * len);
	}
	PdfMixture(Pdf* p0, Pdf* p1)
		:m_len(2),
		m_weight(0.5)
	{
		m_arrPdfs = new Pdf*[2];
		m_arrPdfs[0] = p0;
		m_arrPdfs[1] = p1;
	}
	void SetPdf(int idx, Pdf* pdf)
	{
		assert(idx >= 0 && idx < m_len);
		m_arrPdfs[idx] = pdf;
	}
	

	virtual float Value(const Vector3& direction) const override
	{
		float value = 0.f;
		for (int i = 0; i < m_len; ++i)
		{
			value += m_arrPdfs[i]->Value(direction);
		}
		return value * m_weight;
	}


	virtual Vector3 Generate() const override
	{
		float rand = random.Gen(0.f, m_len - 0.0001f);
		return m_arrPdfs[int(rand)]->Generate();
	}

private:
	int m_len;
	float m_weight;
	Pdf** m_arrPdfs;
};