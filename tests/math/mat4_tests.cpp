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

#include "canvas/math/mat4.h"
#include "canvas/math/transform.h"
#include "gtest/gtest.h"

namespace ca {

TEST(Mat4Test, Basic) {
  Mat4 v1;
  EXPECT_EQ(1.f, v1.row[0].x);
  EXPECT_EQ(0.f, v1.row[0].y);
  EXPECT_EQ(0.f, v1.row[0].z);
  EXPECT_EQ(0.f, v1.row[0].w);
  EXPECT_EQ(0.f, v1.row[1].x);
  EXPECT_EQ(1.f, v1.row[1].y);
  EXPECT_EQ(0.f, v1.row[1].z);
  EXPECT_EQ(0.f, v1.row[1].w);
  EXPECT_EQ(0.f, v1.row[2].x);
  EXPECT_EQ(0.f, v1.row[2].y);
  EXPECT_EQ(1.f, v1.row[2].z);
  EXPECT_EQ(0.f, v1.row[2].w);
  EXPECT_EQ(0.f, v1.row[3].x);
  EXPECT_EQ(0.f, v1.row[3].y);
  EXPECT_EQ(0.f, v1.row[3].z);
  EXPECT_EQ(1.f, v1.row[3].w);
}

TEST(Mat4Test, Blah) {
  Mat4 m;
  m *= translation(Vec3{1.5f, 0.f, 0.f});

  int a = 10;
}

}  // namespace ca
