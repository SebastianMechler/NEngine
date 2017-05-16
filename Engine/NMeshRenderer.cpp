#include "NMeshRenderer.h"

#include "NGlobalData.h"

namespace Nully
{
  void NMeshRenderer::Start()
  {

  }

  void NMeshRenderer::Update(float a_deltaTime)
  {

  }

  bool NMeshRenderer::AddRequiredComponents(IComponentManager * a_componentManager)
  {
    return true;
  }

  NMeshRenderer::NMeshRenderer()
    : m_mesh(NPATH_MESH_CUBE)
    , m_shader(NPATH_SHADER_DEFAULT)
  {
    m_texture.push_back(NPATH_TEXTURE_DEFAULT);
  }

  NMeshRenderer::NMeshRenderer(const char* a_pathToMesh, const char* a_pathToShader, const char* a_pathToTexture)
  {
    if (a_pathToMesh)
    {
      m_mesh = a_pathToMesh;
    }
    else
    {
      m_mesh = NPATH_MESH_CUBE;
    }

    if (a_pathToShader)
    {
      m_shader = a_pathToShader;
    }
    else
    {
      a_pathToShader = NPATH_SHADER_DEFAULT;
    }

    if (a_pathToTexture)
    {
      m_texture.push_back(a_pathToTexture);
    }
    else
    {
      m_texture.push_back(NPATH_TEXTURE_DEFAULT);
    }
  }

  NMeshRenderer::~NMeshRenderer()
  {
  }
  void NMeshRenderer::SetMesh(const char* a_pathMesh)
  {
    m_mesh = a_pathMesh;
  }
  void NMeshRenderer::SetShader(const char* a_pathShader)
  {
    m_shader = a_pathShader;
  }
  void NMeshRenderer::SetTexture(const char* a_texture, uint32_t a_slot)
  {
    if (a_slot <= m_texture.capacity() - 1)
    {
      m_texture[a_slot] = a_texture;
    }
    else
    {
      m_texture.push_back(a_texture);
    }
  }
  const NString& NMeshRenderer::GetMesh()
  {
    return m_mesh;
  }
  const NString& NMeshRenderer::GetShader()
  {
    return m_shader;
  }
  const NVector<NString>& NMeshRenderer::GetTexture()
  {
    return m_texture;
  }
}
