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

#ifndef CANVAS_MATH_MAT4_H_
#define CANVAS_MATH_MAT4_H_

#include "nucleus/logging.h"

#include "canvas/math/vec4.h"

namespace ca {

struct Mat4 {
  Vec4 row[4];

  Mat4() {
    row[0] = Vec4{1.f, 0.f, 0.f, 0.f};
    row[1] = Vec4{0.f, 1.f, 0.f, 0.f};
    row[2] = Vec4{0.f, 0.f, 1.f, 0.f};
    row[3] = Vec4{0.f, 0.f, 0.f, 1.f};
  }

  Mat4(f32 scale) {
    row[0] = Vec4{scale, 0.f, 0.f, 0.f};
    row[1] = Vec4{0.f, scale, 0.f, 0.f};
    row[2] = Vec4{0.f, 0.f, scale, 0.f};
    row[3] = Vec4{0.f, 0.f, 0.f, scale};
  }

  Mat4(const Vec4& row1, const Vec4& row2, const Vec4& row3, const Vec4& row4) {
    row[0] = row1;
    row[1] = row2;
    row[2] = row3;
    row[3] = row4;
  }

  Mat4(f32 v11, f32 v12, f32 v13, f32 v14, f32 v21, f32 v22, f32 v23, f32 v24,
       f32 v31, f32 v32, f32 v33, f32 v34, f32 v41, f32 v42, f32 v43, f32 v44) {
    row[0] = Vec4{v11, v12, v13, v14};
    row[1] = Vec4{v21, v22, v23, v24};
    row[2] = Vec4{v31, v32, v33, v34};
    row[3] = Vec4{v41, v42, v43, v44};
  }

  Vec4& operator[](std::size_t index) {
    DCHECK(index <= 3);
    return row[index];
  }

  const Vec4& operator[](std::size_t index) const {
    DCHECK(index <= 3);
    return row[index];
  }

  float* asArray() { return static_cast<float*>(&row[0].x); }
  const float* asArray() const { return static_cast<const float*>(&row[0].x); }

  bool operator==(const Mat4& other) const {
    for (size_t i = 0; i < 4; ++i) {
      if (row[i] != other.row[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Mat4& other) const {
    for (size_t i = 0; i < 4; ++i) {
      if (row[i] != other.row[i]) {
        return true;
      }
    }
    return false;
  }

  Mat4 operator+(const Mat4& other) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
      result[i] = row[i] + other.row[i];
    }
    return result;
  }

  Mat4& operator+=(const Mat4& other) { return (*this = (*this) + other); }

  Mat4 operator-(const Mat4& other) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i)
      result[i] = row[i] - other.row[i];
    return result;
  }

  Mat4& operator-=(const Mat4& other) { return (*this = (*this) - other); }

  Mat4 Mat4::operator*(const Mat4& other) const {
    const Vec4 srcA0{row[0]};
    const Vec4 srcA1{row[1]};
    const Vec4 srcA2{row[2]};
    const Vec4 srcA3{row[3]};

    const Vec4 srcB0{other.row[0]};
    const Vec4 srcB1{other.row[1]};
    const Vec4 srcB2{other.row[2]};
    const Vec4 srcB3{other.row[3]};

    Mat4 result;
    result[0] = srcA0 * srcB0[0] + srcA1 * srcB0[1] + srcA2 * srcB0[2] +
                srcA3 * srcB0[3];
    result[1] = srcA0 * srcB1[0] + srcA1 * srcB1[1] + srcA2 * srcB1[2] +
                srcA3 * srcB1[3];
    result[2] = srcA0 * srcB2[0] + srcA1 * srcB2[1] + srcA2 * srcB2[2] +
                srcA3 * srcB2[3];
    result[3] = srcA0 * srcB3[0] + srcA1 * srcB3[1] + srcA2 * srcB3[2] +
                srcA3 * srcB3[3];
    return result;
  }

  Mat4& operator*=(const Mat4& other) { return (*this = (*this) * other); }

  Vec4 operator*(const Vec4& other) const {
    return (row[0] * other[0] + row[1] * other[1]) +
           (row[2] * other[2] + row[3] * other[3]);
  }

  Mat4 operator*(f32 scalar) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
      result[i] = row[i] * scalar;
    }
    return result;
  }

  Mat4 operator/(f32 scalar) const {
    Mat4 result;
    for (size_t i = 0; i < 4; ++i) {
      result[i] = row[i] / scalar;
    }
    return result;
  }
};

inline Mat4 transpose(const Mat4& mat) {
  Mat4 result;
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      result[i][j] = mat.row[j][i];
    }
  }
}

#if 0
f32 determinant(const Mat4& mat)
{
  f32 coef00{mat[2][2] * mat[3][3] - mat[3][2] * mat[2][3]};
  f32 coef02{mat[1][2] * mat[3][3] - mat[3][2] * mat[1][3]};
  f32 coef03{mat[1][2] * mat[2][3] - mat[2][2] * mat[1][3]};

  f32 coef04{mat[2][1] * mat[3][3] - mat[3][1] * mat[2][3]};
  f32 coef06{mat[1][1] * mat[3][3] - mat[3][1] * mat[1][3]};
  f32 coef07{mat[1][1] * mat[2][3] - mat[2][1] * mat[1][3]};

  f32 coef08{mat[2][1] * mat[3][2] - mat[3][1] * mat[2][2]};
  f32 coef10{mat[1][1] * mat[3][2] - mat[3][1] * mat[1][2]};
  f32 coef11{mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]};

  f32 coef12{mat[2][0] * mat[3][3] - mat[3][0] * mat[2][3]};
  f32 coef14{mat[1][0] * mat[3][3] - mat[3][0] * mat[1][3]};
  f32 coef15{mat[1][0] * mat[2][3] - mat[2][0] * mat[1][3]};

  f32 coef16{mat[2][0] * mat[3][2] - mat[3][0] * mat[2][2]};
  f32 coef18{mat[1][0] * mat[3][2] - mat[3][0] * mat[1][2]};
  f32 coef19{mat[1][0] * mat[2][2] - mat[2][0] * mat[1][2]};

  f32 coef20{mat[2][0] * mat[3][1] - mat[3][0] * mat[2][1]};
  f32 coef22{mat[1][0] * mat[3][1] - mat[3][0] * mat[1][1]};
  f32 coef23{mat[1][0] * mat[2][1] - mat[2][0] * mat[1][1]};

  Vec4 fac0{coef00, coef00, coef02, coef03};
	Vec4 fac1{coef04, coef04, coef06, coef07};
	Vec4 fac2{coef08, coef08, coef10, coef11};
	Vec4 fac3{coef12, coef12, coef14, coef15};
	Vec4 fac4{coef16, coef16, coef18, coef19};
	Vec4 fac5{coef20, coef20, coef22, coef23};

	Vec4 vec0{m[1][0], m[0][0], m[0][0], m[0][0]};
	Vec4 vec1{m[1][1], m[0][1], m[0][1], m[0][1]};
	Vec4 vec2{m[1][2], m[0][2], m[0][2], m[0][2]};
	Vec4 vec3{m[1][3], m[0][3], m[0][3], m[0][3]};

	Vec4 inv0{vec1 * fac0 - vec2 * fac1 + vec3 * fac2};
	Vec4 inv1{vec0 * fac0 - vec2 * fac3 + vec3 * fac4};
	Vec4 inv2{vec0 * fac1 - vec1 * fac3 + vec3 * fac5};
	Vec4 inv3{vec0 * fac2 - vec1 * fac4 + vec2 * fac5};

	Vec4 signA{+1, -1, +1, -1};
	Vec4 signB{-1, +1, -1, +1};
	Mat4 inverse{inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB};

	Vec4 row0{inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]};

	Vec4 dot0{m[0] * row0};
	f32 dot1{(dot0.x + dot0.y) + (dot0.z + dot0.w)};
	return dot1;
}
#endif  // 0

#if 0
Mat4 inverse(const Mat4& m)
{
	f32 coef00{m[2][2] * m[3][3] - m[3][2] * m[2][3]};
	f32 coef02{m[1][2] * m[3][3] - m[3][2] * m[1][3]};
	f32 coef03{m[1][2] * m[2][3] - m[2][2] * m[1][3]};
	f32 coef04{m[2][1] * m[3][3] - m[3][1] * m[2][3]};
	f32 coef06{m[1][1] * m[3][3] - m[3][1] * m[1][3]};
	f32 coef07{m[1][1] * m[2][3] - m[2][1] * m[1][3]};
	f32 coef08{m[2][1] * m[3][2] - m[3][1] * m[2][2]};
	f32 coef10{m[1][1] * m[3][2] - m[3][1] * m[1][2]};
	f32 coef11{m[1][1] * m[2][2] - m[2][1] * m[1][2]};
	f32 coef12{m[2][0] * m[3][3] - m[3][0] * m[2][3]};
	f32 coef14{m[1][0] * m[3][3] - m[3][0] * m[1][3]};
	f32 coef15{m[1][0] * m[2][3] - m[2][0] * m[1][3]};
	f32 coef16{m[2][0] * m[3][2] - m[3][0] * m[2][2]};
	f32 coef18{m[1][0] * m[3][2] - m[3][0] * m[1][2]};
	f32 coef19{m[1][0] * m[2][2] - m[2][0] * m[1][2]};
	f32 coef20{m[2][0] * m[3][1] - m[3][0] * m[2][1]};
	f32 coef22{m[1][0] * m[3][1] - m[3][0] * m[1][1]};
	f32 coef23{m[1][0] * m[2][1] - m[2][0] * m[1][1]};

	Vec4 fac0{coef00, coef00, coef02, coef03};
	Vec4 fac1{coef04, coef04, coef06, coef07};
	Vec4 fac2{coef08, coef08, coef10, coef11};
	Vec4 fac3{coef12, coef12, coef14, coef15};
	Vec4 fac4{coef16, coef16, coef18, coef19};
	Vec4 fac5{coef20, coef20, coef22, coef23};

	Vec4 vec0{m[1][0], m[0][0], m[0][0], m[0][0]};
	Vec4 vec1{m[1][1], m[0][1], m[0][1], m[0][1]};
	Vec4 vec2{m[1][2], m[0][2], m[0][2], m[0][2]};
	Vec4 vec3{m[1][3], m[0][3], m[0][3], m[0][3]};

	Vec4 inv0{vec1 * fac0 - vec2 * fac1 + vec3 * fac2};
	Vec4 inv1{vec0 * fac0 - vec2 * fac3 + vec3 * fac4};
	Vec4 inv2{vec0 * fac1 - vec1 * fac3 + vec3 * fac5};
	Vec4 inv3{vec0 * fac2 - vec1 * fac4 + vec2 * fac5};

	Vec4 signA{+1, -1, +1, -1};
	Vec4 signB{-1, +1, -1, +1};
	Mat4 inverse{inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB};

	Vec4 row0{inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]};

	Vec4 dot0{m[0] * row0};
	f32 dot1{(dot0.x + dot0.y) + (dot0.z + dot0.w)};

	f32 oneOverDeterminant{1.0f / dot1};
	return inverse * oneOverDeterminant;
}
#endif  // 0

}  // namespace ca

#endif  // CANVAS_MATH_MAT4_H_
