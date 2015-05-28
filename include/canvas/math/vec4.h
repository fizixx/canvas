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

#ifndef CANVAS_MATH_VEC4_H_
#define CANVAS_MATH_VEC4_H_

#include "nucleus/logging.h"

namespace ca {

struct Vec4 {
  float x{0.f};
  float y{0.f};
  float z{0.f};
  float w{0.f};

  Vec4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f)
    : x(x), y(y), z(z), w(w) {}

  float& operator[](std::size_t index) {
    DCHECK(index <= 3);
    return (&x)[index];
  }

  float operator[](std::size_t index) const {
    DCHECK(index <= 3);
    return (&x)[index];
  }
};

}  // namespace ca

#endif  // CANVAS_MATH_VEC2_H_
