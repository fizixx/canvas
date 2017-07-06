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

#include "canvas/rendering/program.h"

#include "nucleus/logging.h"
#include "nucleus/utils/stl.h"

#include "canvas/rendering/shader.h"
#include "canvas/utils/gl_check.h"

namespace ca {

// static
void Program::bind(Program* program) {
  if (program) {
    // Make sure the program is linked.
    if (!program->m_isLinked) {
      program->linkInternal();
    }

    GL_CHECK(glUseProgram(program->m_name));
  } else {
    GL_CHECK(glUseProgram(0));
  }
}

Program::Program() {}

Program::Program(Shader* vertexShader, Shader* fragmentShader)
  : m_vertexShader(vertexShader), m_fragmentShader(fragmentShader) {}

Program::~Program() {
  if (m_name) {
    GL_CHECK(glDeleteProgram(m_name));
  }
}

void Program::setVertexShader(Shader* vertexShader) {
  m_vertexShader = vertexShader;
  m_isLinked = false;
}

void Program::setFragmentShader(Shader* fragmentShader) {
  m_fragmentShader = fragmentShader;
  m_isLinked = false;
}

void Program::link() {
  linkInternal();
}

#define BIND_AND_GET_LOCATION()                                                \
  bind(this);                                                                  \
  GLint location = glGetUniformLocation(m_name, name.c_str());                 \
  if (location == -1 || glGetError() != GL_NO_ERROR) {                         \
    LOG(Warning) << "Could not find uniform location. (" << name << ")";       \
    return false;                                                              \
  }

bool Program::setUniform(std::string name, float f) {
  BIND_AND_GET_LOCATION()
  glUniform1f(location, f);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec2& vec2) {
  BIND_AND_GET_LOCATION()
  glUniform2f(location, vec2.x, vec2.y);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec3& vec3) {
  BIND_AND_GET_LOCATION()
  glUniform3f(location, vec3.x, vec3.y, vec3.z);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Vec4& vec4) {
  BIND_AND_GET_LOCATION()
  glUniform4f(location, vec4.x, vec4.y, vec4.z, vec4.w);
  return glGetError() == GL_NO_ERROR;
}

bool Program::setUniform(std::string name, const Mat4& mat4) {
  BIND_AND_GET_LOCATION()
  glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0].x);
  return glGetError() == GL_NO_ERROR;
}

#undef BIND_AND_GET_LOCATION

void Program::linkInternal() {
  // Make sure the program is created.
  if (!m_name) {
    m_name = glCreateProgram();
  }

  // Attach the shaders.
  GL_CHECK(glAttachShader(m_name, m_vertexShader->getNativeHandle()));
  GL_CHECK(glAttachShader(m_name, m_fragmentShader->getNativeHandle()));

  // Link the program.
  GL_CHECK(glLinkProgram(m_name));

  // Check if there were any information.
  GLint infoLength = 0;
  GL_CHECK(glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &infoLength));

  if (infoLength > 0) {
    std::vector<char> buffer;
    GL_CHECK(glGetProgramInfoLog(m_name, infoLength, &infoLength,
                                 nu::vectorAsArray(&buffer, infoLength)));
    if (infoLength) {
      LOG(Error) << buffer.data();
    }
  }

  m_isLinked = true;
}

}  // namespace ca
