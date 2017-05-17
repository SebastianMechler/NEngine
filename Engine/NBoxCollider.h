#pragma once

#include "IComponent.h"
#include "NVector3.h"
#include "IMesh.h" // for drawing the AABB
#include "NAABB.h"
#include "NTransform.h"

namespace Nully
{
	class NBoxCollider : public IComponent
	{
	public:
		// IComponent Interface
		void Start() override;
		void Update(float a_deltaTime) override;
		bool AddRequiredComponents(IComponentManager* a_componentManager) override;

		NBoxCollider();
		~NBoxCollider();

		IMesh* GetMesh() const;
		void SetMesh(IMesh* a_mesh);

		const NAABB& GetAABB();

		bool Collides(const NBoxCollider& a_boxCollider);

	private:
		IComponentManager* m_componentManager;
		NTransform* m_transform;
		IMesh* m_mesh;
		NAABB m_aabb;
		
	};
}