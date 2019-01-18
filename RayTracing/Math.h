#pragma once
#define MATH_NUM_ANGLES 16384
#define MATH_ANGLE_SHIFT 	2		// Bits to right-shift to get lookup value.
#define MATH_ANGLE_BITS		14		// Number of valid bits in angles.
#define MATH_ANGLE_MASK		(((1<<MATH_ANGLE_BITS)-1)<<(16-MATH_ANGLE_BITS))
#define MATH_KINDA_SMALL_NUMBER	(1.e-4)
extern const float	GSinTable[MATH_NUM_ANGLES];

static const float	kPI = 3.1415926535897932f;

inline int
MathTrunc(float a_f)
{
	return (int)a_f;
}

inline bool MathNearlyZero(float f, float tolerance = MATH_KINDA_SMALL_NUMBER)
{
	return	f > -tolerance&&f < tolerance;
}

template<typename T>
inline T Min(const T a, const T b)
{
	return a <= b ? a : b;
}

template<typename T>
inline T Max(const T a, const T b)
{
	return a >= b ? a : b;
}

inline float MathSinTab(int rotator)
{
	return GSinTable[((rotator >> MATH_ANGLE_SHIFT)&(MATH_NUM_ANGLES - 1))];
}

//------------------------------------------------------------------------
inline float MathCosTab(int rotator)
{
	return GSinTable[(((rotator + 16384) >> MATH_ANGLE_SHIFT)&(MATH_NUM_ANGLES - 1))];
}

//------------------------------------------------------------------------
inline float MathSinFloat(float radian)
{
	return MathSinTab(MathTrunc((radian*65536.f) / (2.f*kPI)));
}

//------------------------------------------------------------------------
inline float MathCosFloat(float radian)
{
	return MathCosTab(MathTrunc((radian*65536.f) / (2.f*kPI)));
}

inline float Square(float f)
{
	return f * f;
}

template<class T>
inline void MathSwap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

