#pragma once

#include "NVector3.h"

namespace Nully
{
	class NAABB
	{
	public:
		NVector3 center;
		NVector3 size;

		void Initialize(const NVector3& a_min, const NVector3& a_max);
		bool Collides(const NAABB& a_aabb);
	};
}
