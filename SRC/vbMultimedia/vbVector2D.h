#ifndef VB_Vector2D_H
#define VB_Vector2D_H

#include "raylib.h"
#include "UtilityMath.h"
#include <cmath>

class vbVector2D
{
public:
    vbVector2D(const float& x = 0.0f, const float& y = 0.0f);
    vbVector2D(const vbVector2D& vector);
    vbVector2D& operator=(const vbVector2D& vector);
    virtual ~vbVector2D();

    const float& x() const;
    float& x();

    const float& y() const;
    float& y();

    const float distance() const;
    const float distance();

    const vbVector2D operator+(const vbVector2D& vector);
    const vbVector2D operator+(const vbVector2D& vector) const;
    const vbVector2D operator*(const float& scale);
    const vbVector2D operator*(const float& scale) const;
    const bool operator==(const vbVector2D& vector);
    const bool operator==(const vbVector2D& vector) const;

    const Vector2 toRaylibVector() const;
    const Vector2 toRaylibVector();

protected:
    float m_x;
    float m_y;
};

inline const float& vbVector2D::x() const
{
    return m_x;
}

inline float& vbVector2D::x()
{
    return const_cast<float&>(static_cast<const vbVector2D&>(*this).x());
}

inline const float& vbVector2D::y() const
{
    return m_y;
}

inline float& vbVector2D::y()
{
    return const_cast<float&>(static_cast<const vbVector2D&>(*this).y());
}

inline const float vbVector2D::distance() const
{
    return std::sqrt(m_x * m_x + m_y * m_y);
}

inline const float vbVector2D::distance()
{
    return static_cast<const vbVector2D&>(*this).distance();
}

inline const vbVector2D vbVector2D::operator+(const vbVector2D& vector) const
{
    return vbVector2D(m_x + vector.m_x, m_y + vector.m_y);
}

inline const vbVector2D vbVector2D::operator+(const vbVector2D& vector)
{
    return static_cast<const vbVector2D&>(*this).operator+(vector);
}

inline const vbVector2D vbVector2D::operator*(const float& scale) const
{
    return vbVector2D(scale * m_x, scale * m_y);
}

inline const vbVector2D vbVector2D::operator*(const float& scale)
{
    return static_cast<const vbVector2D&>(*this).operator*(scale);
}

inline const bool vbVector2D::operator==(const vbVector2D& vector) const
{
    return cmpFloat(m_x, vector.m_x) == 0 && cmpFloat(m_y, vector.m_y) == 0;
}

inline const bool vbVector2D::operator==(const vbVector2D& vector)
{
    return static_cast<const vbVector2D&>(*this).operator==(vector);
}

inline const Vector2 vbVector2D::toRaylibVector() const
{
    return Vector2{ m_x, m_y };
}

inline const Vector2 vbVector2D::toRaylibVector()
{
    return static_cast<const vbVector2D>(*this).toRaylibVector();
}

#endif