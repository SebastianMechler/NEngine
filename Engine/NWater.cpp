#include "NWater.h"

#include "NGlobalData.h"
#include "NMeshRenderer.h"

namespace Nully
{
	NWater::NWater()
	{
		auto meshRenderer = AddComponent<NMeshRenderer>(NWATER_NAME_DEFAULT, NPATH_SHADER_WATER, NPATH_TEXTURE_WATER);
		meshRenderer->SetTexture(NPATH_TEXTURE_TERRAIN_HEIGHTMAP, 1); // add heightmap to slot 1
	}
}
