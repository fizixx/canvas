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

#include "canvas/rendering/geometry.h"

#include "nucleus/macros.h"

namespace ca {

// static
Geometry Geometry::createRectangle(const Rect<f32>& rect, const Color& color) {
  Geometry result;

  Vertex vertices[] = {
      Vertex{Vec3{rect.pos.x, rect.pos.y, 0.f}, Vec2{0.f, 0.f}, color},
      Vertex{Vec3{rect.pos.x + rect.size.width, rect.pos.y, 0.f},
             Vec2{1.f, 0.f}, color},
      Vertex{Vec3{rect.pos.x + rect.size.width, rect.pos.y + rect.size.height,
                  0.f},
             Vec2{1.f, 1.f}, color},
      Vertex{Vec3{rect.pos.x, rect.pos.y + rect.size.height, 0.f},
             Vec2{0.f, 1.f}, color},
  };

  result.addVertices(vertices, ARRAY_SIZE(vertices));

  return result;
}

void Geometry::addVertex(const Vertex& vertex) {
  m_vertices.push_back(vertex);

  m_compiled = false;
}

void Geometry::addVertices(Vertex* vertices, size_t count) {
  m_vertices.reserve(m_vertices.size() + count);
  for (size_t i = 0; i < count; ++i) {
    m_vertices.push_back(vertices[i]);
  }

  m_compiled = false;
}

void Geometry::clear() {
  m_vertices.clear();

  m_compiled = false;
}

void Geometry::compileAndUpload() {
  m_vbo.setData(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
  m_compiled = true;
}

void Geometry::render() const {
  if (!m_compiled) {
    NOTREACHED() << "You have to compile the geometry before you use it.";
    return;
  }

  ca::VertexBufferObject::ScopedBind vboBind(m_vbo);

  // The position channel.
  GL_CHECK(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0));
  GL_CHECK(glEnableVertexAttribArray(0));

  // The texCoord channel.
  GL_CHECK(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                                 (void*)(sizeof(float) * 3)));
  GL_CHECK(glEnableVertexAttribArray(1));

  // The color channel.
  GL_CHECK(glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_FALSE,
                                 sizeof(Vertex), (void*)(sizeof(float) * 5)));
  GL_CHECK(glEnableVertexAttribArray(2));

  glDrawArrays(GL_TRIANGLE_FAN, 0, m_vertices.size());

  GL_CHECK(glDisableVertexAttribArray(2));
  GL_CHECK(glDisableVertexAttribArray(1));
  GL_CHECK(glDisableVertexAttribArray(0));
}

}  // namespace ca
