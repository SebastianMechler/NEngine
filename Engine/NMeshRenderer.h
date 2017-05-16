#pragma once

#include "IComponent.h"
#include "NString.h"
#include "NVector.h"

namespace Nully
{
  class NMeshRenderer : public IComponent
  {
  public:
    // IComponent Interface
    void Start() override;
    void Update(float a_deltaTime) override;
    bool AddRequiredComponents(IComponentManager* a_componentManager) override;

    NMeshRenderer();
    NMeshRenderer(const char* a_pathToMesh, const char* a_pathToShader = nullptr, const char* a_pathToTexture = nullptr);
    ~NMeshRenderer();

    void SetMesh(const char* a_pathMesh);
    void SetShader(const char* a_pathShader);
    void SetTexture(const char* a_texture, uint32_t a_slot = 0);

    const NString& GetMesh();
    const NString& GetShader();
    const NVector<NString>& GetTexture();

  private:
    NString m_mesh; // path to mesh
    NString m_shader; // path to shader
    NVector<NString> m_texture; // path to texture
  };
}