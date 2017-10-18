
#ifndef CANVAS_RENDERING_PROGRAM_H_
#define CANVAS_RENDERING_PROGRAM_H_

#include <string>

#include "nucleus/macros.h"

#include "canvas/math/mat4.h"
#include "canvas/math/vec2.h"
#include "canvas/math/vec3.h"
#include "canvas/math/vec4.h"
#include "canvas/opengl.h"

namespace ca {

class Shader;

class Program {
public:
  // Bind the specified program.  Can pass nullptr to clear the program binding.
  static void bind(Program* program);

  Program();
  Program(Shader* vertexShader, Shader* fragmentShader);
  ~Program();

  // Return the OpenGL resource name for the shader program.
  GLuint getNativeHandle() const { return m_name; }

  // Get/set the vertex shader.
  Shader* getVertexShader() const { return m_vertexShader; }
  void setVertexShader(Shader* vertexShader);

  // Get/set the fragment shader.
  Shader* getFragmentShader() const { return m_fragmentShader; }
  void setFragmentShader(Shader* fragmentShader);

  // Returns true if the program is linked.
  bool isLinked() const { return m_isLinked; }

  // Link the program.
  void link();

  // Set uniforms inside the program.
  bool setUniform(std::string name, float f);
  bool setUniform(std::string name, const Vec2& vec2);
  bool setUniform(std::string name, const Vec3& vec3);
  bool setUniform(std::string name, const Vec4& vec4);
  bool setUniform(std::string name, const Mat4& mat4);

private:
  // Link the program.
  void linkInternal();

  // The native handle to the program.
  GLuint m_name{0};

  // The shaders we'll use.
  Shader* m_vertexShader{nullptr};
  Shader* m_fragmentShader{nullptr};

  // Flag to keep track of whether the program is linked.
  bool m_isLinked{false};

  DISALLOW_COPY_AND_ASSIGN(Program);
};

}  // namespace ca

#endif  // CANVAS_RENDERING_PROGRAM_H_
