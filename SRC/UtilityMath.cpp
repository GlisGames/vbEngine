#include "UtilityMath.h"

float fastInverseSqrt(const float& number, const std::size_t& iterator)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck? 
	y = *(float*)&i;
	for(std::size_t i = 0; i < iterator; ++i)
		y = y * (threehalfs - (x2 * y * y));   // iteration

	return y;
}

Vector2 normalizeVector2(const Vector2& vector2)
{
	float invertDistance = fastInverseSqrt(SQUARE_VECTOR2_DISTANCE(vector2));

	return Vector2{vector2.x * invertDistance, vector2.y * invertDistance};
}

float getAngleFromPoints(const Vector2& origin, const Vector2& destination)
{
	Vector2 vec = Vector2{
		destination.x - origin.x,
		destination.y - origin.y
	};

	Vector2 normVec = normalizeVector2(vec);
	

	return RADIANS_TO_DEGREE(std::asinf(normVec.x));
}

int cmpFloat(const float& first, const float& second, const float& epsilon)
{
	if (std::fabsf(first - second) < epsilon)
		return 0;

	if (first > second)
		return 1;

	return -1;
}
