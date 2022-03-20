#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "raylib.h"
#include <cmath>
#include <utility>
#include <vector>
#include <functional>
#define DEFAULT_CMP_FLOAT_EPSILON 0.01f

#define SQUARE_VECTOR2_DISTANCE(vector2) ((vector2).x * (vector2).x + (vector2).y * (vector2).y)
#define VECTOR2_DISTANCE(vector2) std::sqrt(SQUARE_VECTOR2_DISTANCE(vector2))
#define RADIANS_TO_DEGREE(radian) ((radian) * 57.296) //180 / PI

//reference: https://en.wikipedia.org/wiki/Fast_inverse_square_root
float fastInverseSqrt(const float& number, const std::size_t& iterator = 1);
Vector2 normalizeVector2(const Vector2& vector2);

//Get the angle of the vector from the orgin to destination
//The angle is the angle which can be used for draw graphic object by raylib
float getAngleFromPoints(const Vector2& origin, const Vector2& destination);

//make compare float become safer
int cmpFloat(const float& first, const float& second, const float& epsilon = DEFAULT_CMP_FLOAT_EPSILON);



#endif
