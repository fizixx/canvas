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

#ifndef CANVAS_RENDERING_GEOMETRY_H_
#define CANVAS_RENDERING_GEOMETRY_H_

#include <vector>

#include "nucleus/macros.h"

#include "canvas/rendering/vertex.h"
#include "canvas/rendering/vertex_buffer_object.h"
#include "canvas/utils/color.h"
#include "canvas/utils/rect.h"

namespace ca {

class Geometry {
public:
  // Create a rectangle geometry with the given dimensions.
  static Geometry createRectangle(const Rect<f32>& rect, const Color& color);

  Geometry() = default;
  ~Geometry() = default;

  // Add an array of vertices to the geometry.
  void addVertices(Vertex* vertices, size_t count);

  // Compile and upload the data to the GPU.
  void compileAndUpload();

  // Render the geometry with the given transform applied.
  void render() const;

private:
  // All the vertices we contain.
  std::vector<Vertex> m_vertices;

  // The vertex buffer we use to upload the vertex data to the GPU.
  VertexBufferObject m_vbo;

  // Whether the vertex data was compiled or not.
  bool m_compiled{false};
};

}  // namespace ca

#endif  // CANVAS_RENDERING_GEOMETRY_H_
