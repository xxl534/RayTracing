#pragma once

#include "../vector.h"

class Pdf
{
public:
	virtual float Value(const Vector3& direction) const = 0;
	virtual Vector3 Generate() const = 0;
};