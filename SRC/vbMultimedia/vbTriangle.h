#ifndef VB_TRIANGLE_H
#define VB_TRIANGLE_H

#include "raylib.h"
#include "vbShape.h"
#include "vbGraphicDrawable.h"
#include <array>

//Why am I using this? Just because we have the iterator and be able to know how many elements in the array 
typedef std::array<Vector2, 3> TrianglePoints;

class vbTriangle : public vbShape
{
public:
	vbTriangle(TrianglePoints _points);
	vbTriangle(const vbTriangle& triangle);
	vbTriangle& operator=(const vbTriangle& triangle);
	virtual ~vbTriangle();

	TrianglePoints points;
};

#endif