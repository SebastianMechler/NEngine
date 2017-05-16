#include "NTerrain.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
  NTerrain::NTerrain()
  {
    auto meshRenderer = AddComponent<NMeshRenderer>(NTERRAIN_NAME_DEFAULT, NPATH_SHADER_TERRAIN, NPATH_TEXTURE_TERRAIN);
    meshRenderer->SetTexture(NPATH_TEXTURE_TERRAIN_HEIGHTMAP, 1); // add heightmap to slot 1
  }
}
