#include "NCone.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NCone::NCone()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_CONE, NPATH_SHADER_DEFAULT);
  }
}
