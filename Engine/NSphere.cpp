#include "NSphere.h"

#include "NMeshRenderer.h"
#include "NGlobalData.h"

namespace Nully
{
  NSphere::NSphere()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_SPHERE, NPATH_SHADER_DEFAULT);
  }
}
