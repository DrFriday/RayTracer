#include "GeometricObject.h"

RGBColor
GeometricObject::get_color() const
{
	return color;
}

void
GeometricObject::set_color(const RGBColor newColor)
{
	color = newColor;
}