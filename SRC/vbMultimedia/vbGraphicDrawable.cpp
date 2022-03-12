#include "vbGraphicDrawable.h"

vbGraphicDrawable::vbGraphicDrawable()
{
}

vbGraphicDrawable::vbGraphicDrawable(const vbGraphicDrawable& graphic)
{
}

vbGraphicDrawable& vbGraphicDrawable::operator=(const vbGraphicDrawable& graphic)
{
	return (*this);
}

vbGraphicDrawable::~vbGraphicDrawable()
{
}

vbSingleColourDrawable::vbSingleColourDrawable(Color _colour)
	:vbGraphicDrawable(), colour(_colour)
{
}

vbSingleColourDrawable::vbSingleColourDrawable(const vbSingleColourDrawable& graphic)
	: vbGraphicDrawable(), colour(graphic.colour)
{
}

vbSingleColourDrawable& vbSingleColourDrawable::operator=(const vbSingleColourDrawable& graphic)
{
	vbGraphicDrawable::operator=(graphic);

	this->colour = graphic.colour;

	return (*this);
}

vbSingleColourDrawable::~vbSingleColourDrawable()
{
}

vbRoundedDrawable::vbRoundedDrawable(Color _colour, float _roundness, int _segments)
	:vbSingleColourDrawable(_colour), roundness(_roundness), segments(_segments)
{
}

vbRoundedDrawable::vbRoundedDrawable(const vbRoundedDrawable& graphic)
	:vbSingleColourDrawable(graphic), roundness(graphic.roundness), segments(graphic.segments)
{
}

vbRoundedDrawable& vbRoundedDrawable::operator=(const vbRoundedDrawable& graphic)
{
	vbSingleColourDrawable::operator=(graphic);
	this->roundness = graphic.roundness;
	this->segments = graphic.segments;

	return (*this);
}

vbRoundedDrawable::~vbRoundedDrawable()
{
}
