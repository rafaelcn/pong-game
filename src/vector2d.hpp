
/*
 * Pong Game.
 * Author: Rafael Campos Nunes.
 * License: Apache v2.
 *
 * Fell free to contact me on
 * Email: rafaelnunes737@hotmail.com
 * Github: https://github.com/rafaelcn
 *
 * Also you can contact me on IRC(freenode.net server) my nickname is: ranu.
 */

#ifndef VECTOR2D_H
#define VECTOR2D_H

/**
 * @brief This class abstract a vector behavior, so as with their mathematical
 * operations.
 */
class Vector2D
{
private:
    float X;
    float Y;
public:
    Vector2D(float x_, float y_) : X(x_), Y(y_) {}
    ~Vector2D() {}

    Vector2D& operator ()();
    Vector2D operator +(const Vector2D& rhs) const;
    Vector2D operator - ();
    Vector2D operator - (const Vector2D& rhs) const;
    Vector2D operator *(const float scalar);
    Vector2D& operator +=(const Vector2D &rhs);

    Vector2D cross(const Vector2D other) const;
    Vector2D normalized() const;

    float x() const;
    float y() const;
    void x(float x_);
    void y(float y_);

    float magnitude();
    float magnitude_squared();

    float dot(const Vector2D& other) const;

    void normalize();


};

#endif // VECTOR2D_H
