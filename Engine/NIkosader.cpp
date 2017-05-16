#include "NIkosader.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NIkosader::NIkosader()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NPATH_MESH_IKOSADER, NPATH_SHADER_DEFAULT);
  }
}
