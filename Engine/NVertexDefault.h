#pragma once

#include "NVector2.h"
#include "NVector4.h"
#include "NVector3.h"

namespace Nully
{
	struct NVertexDefault
	{
		NVector3 position;
		NVector4 color;
		NVector3 normal;
		NVector2 uv;
	};
}
