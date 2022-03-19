#include "vbVector2D.h"

vbVector2D::vbVector2D(const float& x, const float& y)
    :m_x(x), m_y(y)
{

}

vbVector2D::vbVector2D(const vbVector2D& vector)
    : m_x(vector.m_x), m_y(vector.m_y)
{

}

vbVector2D& vbVector2D::operator=(const vbVector2D& vector)
{
    m_x = vector.m_x;
    m_y = vector.m_y;

    return (*this);
}

vbVector2D::~vbVector2D()
{

}