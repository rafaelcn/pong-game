#pragma once

/**
 * @brief A representation of a vector of two float components.
 */
class Vector2D
{
private:
  float X;
  float Y;
public:
  Vector2D(float x, float y) : X(x), Y(y) {}
  Vector2D(const Vector2D& o): X(o.x()), Y(o.y()) {}
  ~Vector2D() {}

  Vector2D& operator ()();
  Vector2D operator +(const Vector2D& rhs) const;
  Vector2D operator -();
  Vector2D operator -(const Vector2D& rhs) const;
  Vector2D operator *(const float scalar);
  Vector2D& operator +=(const Vector2D &rhs);
  Vector2D& operator -=(const Vector2D &rhs);

  bool operator <(const Vector2D &rhs);
  bool operator >=(const Vector2D &rhs);

  Vector2D cross(const Vector2D other) const;
  Vector2D normalized() const;

  float x() const;
  float y() const;
  void x(float x);
  void y(float y);

  float magnitude() const;
  float magnitude_squared() const;

  float dot(const Vector2D& other) const;

  void normalize();
};
