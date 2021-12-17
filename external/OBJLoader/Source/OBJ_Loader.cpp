#include "OBJ_Loader.h"

objl::Vector3 objl::math::CrossV3(const Vector3 a, const Vector3 b)
{
	return Vector3(a.Y * b.Z - a.Z * b.Y,
	               a.Z * b.X - a.X * b.Z,
	               a.X * b.Y - a.Y * b.X);
}

float objl::math::MagnitudeV3(const Vector3 in)
{
	return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
}

float objl::math::DotV3(const Vector3 a, const Vector3 b)
{
	return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
}

float objl::math::AngleBetweenV3(const Vector3 a, const Vector3 b)
{
	float angle = DotV3(a, b);
	angle /= (MagnitudeV3(a) * MagnitudeV3(b));
	return angle = acosf(angle);
}
