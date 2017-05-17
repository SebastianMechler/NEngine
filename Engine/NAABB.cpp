#include "NAABB.h"
namespace Nully
{
	void NAABB::Initialize(const NVector3& a_min, const NVector3& a_max)
	{
		this->size = (a_max - a_min) / 2.0f;
		this->center = a_min + size;
	}
	bool NAABB::Collides(const NAABB& a_aabb)
	{
		NVector3 ra = size + a_aabb.size;

		return (center.x - a_aabb.center.x + ra.x <= 2 * ra.x)
			&& (center.y - a_aabb.center.y + ra.y <= 2 * ra.y)
			&& (center.z - a_aabb.center.z + ra.z <= 2 * ra.z);
	}
}
