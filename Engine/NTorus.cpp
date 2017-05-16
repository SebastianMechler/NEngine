#include "NTorus.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NTorus::NTorus()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_TORUS, NPATH_SHADER_DEFAULT);
  }
}