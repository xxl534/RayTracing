#include <cmath>
#include "vector.h"

inline bool
Vector3::operator==(const Vector3& a_rhs) const
{
	return x == a_rhs.x && y == a_rhs.y && z == a_rhs.z;
}

//-------------------------------------------------------------------------

inline bool
Vector3::operator!=(const Vector3& a_rhs) const
{
	return x != a_rhs.x || y != a_rhs.y || z != a_rhs.z;
}

inline bool 
Vector3::operator>(const Vector3& a_rhs) const
{
	return x > a_rhs.x && y > a_rhs.y && z > a_rhs.z;
}

inline bool
Vector3::operator>=(const Vector3& a_rhs) const
{
	return x >= a_rhs.x && y >= a_rhs.y && z >= a_rhs.z;
}

inline bool
Vector3::operator<(const Vector3& a_rhs) const
{
	return x < a_rhs.x && y < a_rhs.y && z < a_rhs.z;
}

inline bool
Vector3::operator<=(const Vector3& a_rhs) const
{
	return x <= a_rhs.x && y <= a_rhs.y && z <= a_rhs.z;
}

//-------------------------------------------------------------------------

inline Vector3&
Vector3::operator-=(const Vector3& a_rhs)
{
	x -= a_rhs.x;
	y -= a_rhs.y;
	z -= a_rhs.z;
	return *this;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator-(const Vector3& a_rhs) const
{
	Vector3 v(*this);
	v -= a_rhs;
	return v;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

//-------------------------------------------------------------------------

inline Vector3&
Vector3::operator+=(const Vector3& a_rhs)
{
	x += a_rhs.x;
	y += a_rhs.y;
	z += a_rhs.z;
	return *this;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator+(const Vector3& a_rhs) const
{
	Vector3 v(*this);
	v += a_rhs;
	return v;
}

//-------------------------------------------------------------------------

inline Vector3&
Vector3::operator*=(float a_f)
{
	x *= a_f;
	y *= a_f;
	z *= a_f;
	return *this;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator*(float a_f) const
{
	Vector3 v(*this);
	v *= a_f;
	return v;
}

//-------------------------------------------------------------------------

inline Vector3&
Vector3::operator*=(const Vector3& a_rhs)
{
	x *= a_rhs.x;
	y *= a_rhs.y;
	z *= a_rhs.z;
	return *this;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator*(const Vector3& a_rhs) const
{
	Vector3 v(*this);
	v *= a_rhs;
	return v;
}
//-------------------------------------------------------------------------

inline Vector3&
Vector3::operator/=(float a_f)
{
	return this->operator *=(1.f / a_f);
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::operator/(float a_f) const
{
	Vector3 v(*this);
	v /= a_f;
	return v;
}

//-------------------------------------------------------------------------

inline float
Vector3::dot(const Vector3& a_rhs) const
{
	return x * a_rhs.x + y * a_rhs.y + z * a_rhs.z;
}

//-------------------------------------------------------------------------

inline Vector3
Vector3::cross(const Vector3& a_rhs) const
{
	float t_x = y * a_rhs.z - z * a_rhs.y;
	float t_y = z * a_rhs.x - x * a_rhs.z;
	float t_z = x * a_rhs.y - y * a_rhs.x;
	return Vector3(t_x, t_y, t_z);
}

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
Vector3&
Vector3::Lerp(const Vector3& a_v, float a_fFactor)
{
	float fNegFactor = 1 - a_fFactor;
	x = fNegFactor * x + a_fFactor * a_v.x;
	y = fNegFactor * y + a_fFactor * a_v.y;
	z = fNegFactor * z + a_fFactor * a_v.z;
	return *this;
}

//----------------------------------------
Vector3
Vector3::GetLerp(const Vector3& a_v, float a_fFactor) const
{
	Vector3 vTmp(*this);
	vTmp.Lerp(a_v, a_fFactor);
	return vTmp;
}

//----------------------------------------
Vector3&
Vector3::Abs()
{
	x = (float)abs(x);
	y = (float)abs(y);
	z = (float)abs(z);
}

//----------------------------------------
Vector3
Vector3::GetAbs() const
{
	Vector3 vTmp(*this);
	vTmp.Abs();
	return vTmp;
}

//----------------------------------------
Vector3&
Vector3::Normalize()
{
	double dLenSqr = (double)(x * x) + (y * y) + (z * z);
	if (dLenSqr > 0.0)
	{
		float fLenRecp = (float)(1.f / sqrt(dLenSqr));
		x *= fLenRecp;
		y *= fLenRecp;
		z *= fLenRecp;
	}
	return *this;
}

//----------------------------------------
Vector3
Vector3::GetNormalize() const
{
	Vector3 vTmp(*this);
	vTmp.Normalize();
	return vTmp;
}

//----------------------------------------
float Vector3::Length() const
{
	double dLenSqr = (double)(x * x) + (y * y) + (z * z);
	return (float)sqrt(dLenSqr);
}

//----------------------------------------
float
Vector3::LengthSqr() const
{
	return x*x + y*y + z*z;;
}

//----------------------------------------
void
Vector3::FindBestAxisVectors(Vector3& a_vAxis1, Vector3& a_vAxis2)
{
	Normalize();
	Vector3 vAbs = GetAbs();

	if (vAbs.z > vAbs.x && vAbs.z > vAbs.y)
	{
		a_vAxis1 = Vector3(1.f, 0.f, 0.f);
	}
	else
	{
		a_vAxis1 = Vector3(0.f, 0.f, 1.f);
	}

	a_vAxis1 = (a_vAxis1 - *this * (a_vAxis1.dot(*this)));
	a_vAxis1.Normalize();
	a_vAxis2 = a_vAxis1.cross(*this);
}

//----------------------------------------
Vector3&
Vector3::Set(float a_fx, float a_fy, float a_fz)
{
	x = a_fx;
	y = a_fy;
	z = a_fz;
}

void
Vector3::RotateYZBy(float a_fDegrees, const Vector3& a_vecCenter /*= Vector3(0.f, 0.f, 0.f)*/)
{
	a_fDegrees *= kPIDivide180;
	float cs = MathCosFloat(a_fDegrees);
	float sn = MathSinFloat(a_fDegrees);
	z -= a_vecCenter.z;
	y -= a_vecCenter.y;
	Set(x, y*cs - z*sn, y*sn + z*cs);
	z += a_vecCenter.z;
	y += a_vecCenter.y;
}

//----------------------------------------
void
Vector3::RotateXZBy(float a_fDegrees, const Vector3& a_vecCenter /*= Vector3(0.f, 0.f, 0.f)*/)
{
	a_fDegrees *= kPIDivide180;
	float cs = MathCosFloat(a_fDegrees);
	float sn = MathSinFloat(a_fDegrees);
	x -= a_vecCenter.x;
	z -= a_vecCenter.z;
	Set(x*cs - z*sn, y, x*sn + z*cs);
	x += a_vecCenter.x;
	z += a_vecCenter.z;
}

//----------------------------------------
void
Vector3::RotateXYBy(float a_fDegrees, const Vector3& a_vecCenter /*= Vector3(0.f, 0.f, 0.f)*/)
{
	a_fDegrees *= kPIDivide180;
	float cs = MathCosFloat(a_fDegrees);
	float sn = MathSinFloat(a_fDegrees);
	x -= a_vecCenter.x;
	y -= a_vecCenter.y;
	Set(x*cs - y*sn, x*sn + y*cs, z);
	x += a_vecCenter.x;
	y += a_vecCenter.y;
}
//----------------------------------------
const Vector3&
Vector3::Zero()
{
	return ms_vZero;
}

inline Vector3 
Vector3::Reflect(const Vector3 & v, const Vector3 & vNormal)
{
	return v - vNormal * 2.f * v.dot(vNormal);
}

inline bool 
Vector3::Refract(const Vector3& vIn, const Vector3& vNormal, float fRefractiveRadio, Vector3& out_vRefracted)
{
	float dt = vIn.dot(vNormal);
	float discriminant = 1.f - fRefractiveRadio * fRefractiveRadio * (1 - dt * dt);
	if (discriminant > 0)
	{
		out_vRefracted = (vIn - vNormal * dt) * fRefractiveRadio - vNormal * sqrtf(discriminant);
		return true;
	}
	return false;
}

inline Vector3 
Vector3::MergeMin(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(Min(lhs.x, rhs.x), Min(lhs.y, rhs.y), Min(lhs.z, rhs.z));
}

inline Vector3 
Vector3::MergeMax(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(Max(lhs.x, rhs.x), Max(lhs.y, rhs.y), Max(lhs.z, rhs.z));
}