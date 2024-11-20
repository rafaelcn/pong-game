#pragma once

/**
 * Copyright 2014-2018 Rafael Campos Nunes.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain a
 * copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

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
    ~Vector2D() {}

    Vector2D& operator ()();
    Vector2D operator +(const Vector2D& rhs) const;
    Vector2D operator -();
    Vector2D operator -(const Vector2D& rhs) const;
    Vector2D operator *(const float scalar);
    Vector2D& operator +=(const Vector2D &rhs);
    Vector2D& operator <(const Vector2D &rhs);

    Vector2D cross(const Vector2D other) const;
    Vector2D normalized() const;

    float x() const;
    float y() const;
    void x(float x);
    void y(float y);

    float magnitude();
    float magnitude_squared();

    float dot(const Vector2D& other) const;

    void normalize();
};
