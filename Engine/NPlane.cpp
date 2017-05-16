#include "NPlane.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NPlane::NPlane()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_PLANE, NPATH_SHADER_DEFAULT);
  }
}
