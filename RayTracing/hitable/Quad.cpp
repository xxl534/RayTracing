#include "Quad.h"
#include <float.h>
#include "../Random.h"
extern RandomFloat random;

Quad::Quad(const Vector3 & pos, const Vector3 & normal, const Vector3 & up, float width, float height, Material* pMat)
	:m_position(pos)
	,m_width(width)
	,m_height(height)
	,m_pMaterial(pMat)
{

	m_normal = normal.GetNormalize();
	m_right = up.cross(normal).GetNormalize();
	m_up = m_normal.cross(m_right);
	Vector3 v0 = m_position + m_right * width * (-0.5f) + m_up * m_height * 0.5f;
	Vector3 v1 = v0 + m_right * width;
	Vector3 v2 = v0 - m_up * height;
	Vector3 v3 = v1 - m_up * height;
	Vector3 vMin = Vector3::MergeMin(Vector3::MergeMin(v0, v1), Vector3::MergeMin(v2, v3)) - Vector3(0.01f);
	Vector3 vMax = Vector3::MergeMax(Vector3::MergeMax(v0, v1), Vector3::MergeMax(v2, v3)) + Vector3(0.01f);
	m_aabb = Aabb(vMin, vMax);
}

bool Quad::Hit(const Ray& ray, float fMinCoef, float fMaxCoef, HitRecord& rec) const
{
	float fDotDN = ray.Direction().dot(m_normal);
	if ( fDotDN >= 0)
	{
		return false;
	}
	float t = -(ray.Origin() - m_position).dot(m_normal) / fDotDN;
	if (t > fMinCoef && t < fMaxCoef)
	{
		Vector3 point = ray.PointAt(t);
		Vector3 vDelta = point - m_position;
		float u = vDelta.dot(m_right) / m_width + 0.5f;
		if (u < 0.f || u > 1.f)
		{
			return false;
		}
		float v = vDelta.dot(m_up) / m_height + 0.5f;
		if (v < 0.f || v > 1.f)
		{
			return false;
		}
		rec.coef = t;
		rec.u = u;
		rec.v = v;
		rec.point = point;
		rec.normal = m_normal;
		rec.material_ptr = m_pMaterial;
		return true;
	}
	return false;
}

Aabb Quad::GetAabb()
{
	return m_aabb;
}

float Quad::PdfValue(const Vector3& origin, const Vector3 direction) const
{
	HitRecord rec;
	Ray ray(origin, direction);
	if (Hit(ray, 0.001f, FLT_MAX, rec))
	{
		float area = m_height * m_width;
		float distanceSqr = rec.coef * rec.coef;
		float cosine = Abs(rec.normal.dot(ray.Direction()));
		return distanceSqr / (cosine * area);
	}
	return 0.f;
}

Vector3 Quad::Random(const Vector3& origin) const
{
	Vector3 randomPoint = m_position + m_up * random.Gen(-0.5f, 0.5f) + m_right * random.Gen(-0.5f, 0.5f);
	return randomPoint - origin;
}

