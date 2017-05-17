#include "NBoxCollider.h"
#include "NMeshRenderer.h"
#include "NMeshManager.h"
#include "NMemory.h"
#include "NVertexDefault.h"
#include "NObjectManager.h"
#include "NTransform.h"

namespace Nully
{
	void NBoxCollider::Start()
	{
		auto meshRenderer = m_componentManager->GetComponent<NMeshRenderer>();
		if (!meshRenderer)
		{
			return;
		}


		auto mesh = NMeshManager::GetInstance().GetMesh(meshRenderer->GetMesh());
		if (!mesh)
		{
			return;
		}

		m_transform = m_componentManager->GetComponent<NTransform>();

		m_aabb.Initialize(mesh->GetBoundingMin(), mesh->GetBoundingMax());	
	}
	void NBoxCollider::Update(float a_deltaTime)
	{
		
		// check all objects for BoxCollider
		// is colliding?
		// set velocity vector to zero
		// no rotation...
		// no scaling...

		// check all drawable objects
		auto drawableObjects = NObjectManager::GetInstance().GetDrawableObjects();
		for (auto& e : drawableObjects)
		{
			auto boxCollider = e.second->GetComponent<NBoxCollider>();

			if (boxCollider && boxCollider != this) // no self collision
			{
				if (this->Collides(*boxCollider))
				{
					m_transform->SetPosition(0.0f, 0.0f, 0.0f);
					return;
				}
			}
		}

		// check all other objects
		auto objects = NObjectManager::GetInstance().GetObjects();
		for (auto& e : objects)
		{
			auto boxCollider = e->GetComponent<NBoxCollider>();

			if (boxCollider && boxCollider != this) // no self collision
			{
				if (this->Collides(*boxCollider))
				{
					return;
				}
			}
		}

		// check camera.. lol
		auto camera = NObjectManager::GetInstance().GetCamera();
		if (camera && camera->GetComponent<NBoxCollider>())
		{
			auto boxCollider = camera->GetComponent<NBoxCollider>();

			if (boxCollider && boxCollider != this) // no self collision
			{
				if (this->Collides(*boxCollider))
				{
					return;
				}
			}
		}

	}
	bool NBoxCollider::AddRequiredComponents(IComponentManager* a_componentManager)
	{
		m_componentManager = a_componentManager;

		return true;
	}
	NBoxCollider::NBoxCollider()
		: m_mesh(nullptr)
	{
	}
	NBoxCollider::~NBoxCollider()
	{
		NSafeDelete(m_mesh);
	}
	IMesh* NBoxCollider::GetMesh() const
	{
		return m_mesh;
	}
	void NBoxCollider::SetMesh(IMesh* a_mesh)
	{
		if (m_mesh)
		{
			NSafeDelete(m_mesh);
		}

		m_mesh = a_mesh;
	}
	const NAABB& NBoxCollider::GetAABB()
	{
		return m_aabb;
	}
	bool NBoxCollider::Collides(const NBoxCollider& a_boxCollider)
	{
		NVector3 ra = this->m_aabb.size + a_boxCollider.m_aabb.size;

		NVector3 thisWorld;
		thisWorld.x = m_transform->GetPosition().x;
		thisWorld.y = m_transform->GetPosition().y;
		thisWorld.z = m_transform->GetPosition().z;

		NVector3 otherWorld;
		otherWorld.x = a_boxCollider.m_transform->GetPosition().x;
		otherWorld.y = a_boxCollider.m_transform->GetPosition().y;
		otherWorld.z = a_boxCollider.m_transform->GetPosition().z;


		bool result = ((abs((thisWorld.x + this->m_aabb.center.x) - (otherWorld.x + a_boxCollider.m_aabb.center.x)) <= ra.x)
			&& (abs((thisWorld.y + this->m_aabb.center.y) - (otherWorld.y + a_boxCollider.m_aabb.center.y)) <= ra.y)
			&& (abs((thisWorld.z + this->m_aabb.center.z) - (otherWorld.z + a_boxCollider.m_aabb.center.z)) <= ra.z));

		return result;
	}
}
