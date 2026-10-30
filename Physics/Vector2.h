#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>

class Vector2
{
public:

    float x;
    float y;

    Vector2(float x = 0.0f, float y = 0.0f)
        : x(x), y(y)
    {
    }

    Vector2 operator+(const Vector2& other) const
    {
        return Vector2(
            x + other.x,
            y + other.y
        );
    }

    Vector2 operator-(const Vector2& other) const
    {
        return Vector2(
            x - other.x,
            y - other.y
        );
    }

    Vector2 operator*(float scalar) const
    {
        return Vector2 (
            x * scalar,
            y * scalar 
        );
    }

    Vector2 operator/(float scalar) const
    {
        return Vector2(
            x / scalar,
            y / scalar
        );
    }

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;

        return *this;

    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;

        return *this;
    }

    float length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vector2 normalized() const
    {
        float len = length();

        if (len == 0.0f)
            return Vector2(0,0);
        
        return *this / len;
    }

    static float dot(
        const Vector2& a,
        const Vector2& b

    )
    {
        return a.x * b.x + a.y * b.y;

    }
};

#endif