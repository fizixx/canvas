// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef CANVAS_MATH_VEC2_H_
#define CANVAS_MATH_VEC2_H_

#include <cmath>

#include "nucleus/logging.h"
#include "nucleus/types.h"

namespace ca {

struct Vec2 {
  F32 x{0.f};
  F32 y{0.f};

  explicit Vec2(F32 x = 0.f, F32 y = 0.f) : x{x}, y{y} {}

  F32& operator[](USize index) {
    DCHECK(index <= 1);
    return (&x)[index];
  }

  F32 operator[](USize index) const {
    DCHECK(index <= 1);
    return (&x)[index];
  }

  // Comparison

  bool operator==(const Vec2& right) const {
    return x == right.x && y == right.y;
  }

  bool operator!=(const Vec2& right) const {
    return x != right.x || y != right.y;
  }

  // Arithmatic

  Vec2 operator-() const { return Vec2{-x, -y}; }

  Vec2 operator+(const Vec2& right) const {
    return Vec2{x + right.x, y + right.y};
  }

  Vec2& operator+=(const Vec2& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 operator-(const Vec2& right) const {
    return Vec2{x - right.x, y - right.y};
  }

  Vec2& operator-=(const Vec2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 operator*(F32 scalar) const { return Vec2{x * scalar, y * scalar}; }

  Vec2& operator*=(F32 scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 operator/(F32 scalar) const { return Vec2{x / scalar, y / scalar}; }

  Vec2& operator/=(F32 scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
  }
};

inline F32 dotProduct(const Vec2& a, const Vec2& b) {
  return a.x * b.x + a.y * b.y;
}

inline F32 crossProduct(const Vec2& a, const Vec2& b) {
  return a.x * b.y - b.x * a.y;
}

inline F32 lengthSquared(const Vec2& a) {
  return dotProduct(a, a);
}

inline F32 length(const Vec2& a) {
  return std::sqrt(lengthSquared(a));
}

inline Vec2 normalize(const Vec2& a) {
  return a * (1.f / length(a));
}

}  // namespace ca

#endif  // CANVAS_MATH_VEC2_H_
