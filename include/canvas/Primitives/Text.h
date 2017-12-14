
#ifndef CANVAS_RENDERING_TEXT_H_
#define CANVAS_RENDERING_TEXT_H_

#include <string>

#include "canvas/math/mat4.h"
#include "canvas/rendering/geometry.h"
#include "nucleus/Macros.h"

namespace ca {

class Canvas;
class Font;

class Text {
public:
  Text();
  explicit Text(Font* font, I32 textSize = 30, const std::string& text = std::string{});
  ~Text() = default;

  // Get/set the font used to render the text.
  Font* getFont() const { return m_font; }
  void setFont(Font* font);

  // Set the text we want to render.
  void setText(const std::string& text);

  // Set the size of the text we want to render.
  void setTextSize(I32 textSize);

  // Get the bounds of the text we're rendering.
  const Rect<I32>& getBounds() const { return m_bounds; }

  // Render the text.
  void render(Canvas* canvas, const Mat4& transform) const;

private:
  // Make sure the shaders for text rendering is initialized.
  void ensureShaders();

  // Take the font and create the geometry we use to render the text glyphs.
  void updateGeometry();

  // The font we want to render.
  Font* m_font{nullptr};

  // The text we want to render.
  std::string m_text;

  // The size of the text we want to render.
  I32 m_textSize{30};

  // The geometry we render.
  Geometry m_geometry{Geometry::Triangles};

  // The bounds of the geometry.
  Rect<I32> m_bounds;

  DISALLOW_COPY_AND_ASSIGN(Text);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_TEXT_H_
