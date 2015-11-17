#include "vector2d.hpp"

#include <cmath>

Vector2D::Vector2D(float x_, float y_) : X(x_), Y(y_)
{}

Vector2D::~Vector2D()
{}

Vector2D& Vector2D::operator ()()
{
    return *this;
}

Vector2D Vector2D::operator +(const Vector2D& rhs) const
{
    return Vector2D(X + rhs.X, Y + rhs.Y);
}

Vector2D Vector2D::operator -()
{
    return Vector2D(-X, -Y);
}

Vector2D Vector2D::operator -(const Vector2D& rhs) const
{
    return Vector2D(X - rhs.X, Y - rhs.Y);
}

Vector2D Vector2D::operator *(const float scalar)
{
    return Vector2D(X * scalar, Y * scalar);
}

Vector2D& Vector2D::operator +=(const Vector2D& rhs)
{
    X += rhs.X;
    Y += rhs.Y;

    return *this;
}

float Vector2D::magnitude()
{
    return sqrt((pow(X, 2) + pow(Y, 2)));
}

float Vector2D::magnitude_squared()
{
    return pow(magnitude(), 2);
}

float Vector2D::x() const
{
    return X;
}

float Vector2D::y() const
{
    return Y;
}

void Vector2D::x(const float x_)
{
    X = x_;
}

void Vector2D::y(const float y_)
{
    Y = y_;
}

float Vector2D::dot(const Vector2D& other) const
{
    return (X * other.X) + (Y * other.Y);
}

Vector2D Vector2D::cross(const Vector2D other) const
{
    return Vector2D(X * other.X, Y * other.Y);
}
