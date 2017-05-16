#include "NCube.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NCube::NCube()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_CUBE, NPATH_SHADER_DEFAULT);
  }
}
