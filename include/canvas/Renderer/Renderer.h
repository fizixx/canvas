

#ifndef CANVAS_RENDERER_RENDERER_H_
#define CANVAS_RENDERER_RENDERER_H_

#include "canvas/Renderer/Command.h"
#include "canvas/Renderer/Types.h"
#include "canvas/Renderer/UniformBuffer.h"
#include "canvas/Renderer/VertexDefinition.h"
#include "canvas/Utils/Image.h"
#include "canvas/Utils/ShaderSource.h"
#include "canvas/Utils/Size.h"
#include "nucleus/Containers/DynamicArray.h"

namespace ca {

class Renderer {
public:
  Renderer();
  ~Renderer();

  ProgramId createProgram(const ShaderSource& vertexShader, const ShaderSource& fragmentShader);

  VertexBufferId createVertexBuffer(const VertexDefinition& bufferDefinition, void* data,
                                    MemSize dataSize);
  void vertexBufferData(VertexBufferId id, void* data, MemSize dataSize);
  void deleteVertexBuffer(VertexBufferId id);

  IndexBufferId createIndexBuffer(ComponentType componentType, void* data, MemSize dataSize);
  void indexBufferData(IndexBufferId id, void* data, MemSize dataSize);
  void deleteIndexBuffer(IndexBufferId id);

  TextureId createTexture(const Image& image);

  UniformId createUniform(const nu::StringView& name);

  const ca::Size& getSize() const {
    return m_size;
  }

  // Resize the rendering area. Typically called when the window is resized.
  void resize(const Size& size);

  void beginFrame();
  void endFrame();

  void clear(const Color& color);

  void draw(DrawType drawType, U32 indexCount, ProgramId programId, VertexBufferId vertexBufferId,
            IndexBufferId indexBufferId, TextureId textureId, const UniformBuffer& uniforms);

private:
  DELETE_COPY_AND_MOVE(Renderer);

  struct ProgramData {
    U32 id;
  };

  struct VertexBufferData {
    U32 id;
  };

  struct IndexBufferData {
    U32 id;
    ComponentType componentType;
  };

  struct TextureData {
    U32 id;
    Size size;
  };

  struct UniformData {
    nu::StaticString<128> name;
  };

  Size m_size;

  nu::DynamicArray<ProgramData> m_programs;
  nu::DynamicArray<VertexBufferData> m_vertexBuffers;
  nu::DynamicArray<IndexBufferData> m_indexBuffers;
  nu::DynamicArray<TextureData> m_textures;
  nu::DynamicArray<UniformData> m_uniforms;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_RENDERER_H_
