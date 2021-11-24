#ifndef VBPROPERTY_H
#define VBPROPERTY_H

#include "vbEngine.h"
template <class T>
class vbProperty
{
public:
	vbProperty(T initValue);
	T value;
};

#endif