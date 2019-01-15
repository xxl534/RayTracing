#pragma once
struct Vector3
{
	union
	{
		struct
		{
			float x, y, z;
		};
		float f[3];
	};

	bool			operator==(const Vector3& a_rhs) const;
	bool			operator!=(const Vector3& a_rhs) const;
	Vector3&	operator-=(const Vector3& a_rhs);
	Vector3		operator-(const Vector3& a_rhs) const;
	Vector3		operator-() const;
	Vector3&	operator+=(const Vector3& a_rhs);
	Vector3		operator+(const Vector3& a_rhs) const;
	Vector3&	operator*=(float a_f);
	Vector3		operator*(float a_f) const;
	Vector3&	operator*=(const Vector3& a_rhs);
	Vector3		operator*(const Vector3& a_rhs) const;
	Vector3&	operator/=(float a_f);
	Vector3		operator/(float a_f) const;
	float			dot(const Vector3& a_rhs) const;
	Vector3		cross(const Vector3& a_rhs) const;

	Vector3()
	{

	}

	Vector3(float a_f)
	{
		x = a_f;
		y = a_f;
		z = a_f;
	}
	Vector3(float a_fx, float a_fy, float a_fz)
	{
		x = a_fx;
		y = a_fy;
		z = a_fz;
	}

	Vector3(const float* a_p)
	{
		x = a_p[0];
		y = a_p[1];
		z = a_p[2];
	}

	inline Vector3&		Lerp(const Vector3& a_v, float a_fFactor);
	inline Vector3			GetLerp(const Vector3& a_v, float a_fFactor) const;
	inline Vector3&		Abs();
	inline Vector3			GetAbs() const;
	inline Vector3&		Normalize();
	inline Vector3			GetNormalize() const;
	inline float			Length() const;
	inline float			LengthSqr() const;
	inline void				FindBestAxisVectors(Vector3& a_vAxis1, Vector3& a_vAxis2);
	inline Vector3&		Set(float a_fx, float a_fy, float a_fz);

	inline static const Vector3&	Zero();
	inline static Vector3		Reflect(const Vector3& v, const Vector3& vNormal);
	inline static bool			Refract(const Vector3& v, const Vector3& vNormal, float fRefractiveRadio, Vector3& out_vRefracted);
private:
	static Vector3			ms_vZero;
};

#include "vector.inl"