#ifndef VB_SHAPE_H
#define VB_SHAPE_H
#include "vbGraphicObject.h"

enum TYPE_SHAPE 
{
	UNDEFINED = 0,
	RECTANGLE = 1,
	CIRCLE = 2,
	TRIANGLE = 3
};

class vbShape : public vbGraphicObject
{
public:
	//when you create new shape, remember to set the TYPE_SHAPE for it
	vbShape(const TYPE_SHAPE& type);
	vbShape(const vbShape& shape);
	vbShape& operator=(const vbShape& shape);
	virtual ~vbShape();

	//Don't assign the UNDEFINED here, this must be done by contructor
	const TYPE_SHAPE TYPE;
};


#endif