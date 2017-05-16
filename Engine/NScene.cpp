#include "NScene.h"

#include "NGameObject.h"
#include "NCameraDirectX.h"
#include "NPlayerController.h"
#include "NObjectManager.h"
#include "NMeshRenderer.h"
#include "NPrimitive.h"
#include "NGlobalData.h"
#include "NTerrain.h"
#include "NWater.h"

namespace Nully
{
  bool NScene::Initialize()
  {
    // create camera
    auto gCamera = NGameObject::Instantiate<NGameObject>(false);
    auto t = gCamera->GetComponent<NTransform>();
    t->SetPosition(0.0f, 2.0f, -5.0f);
    gCamera->AddComponent<NCameraDirectX>();
    NObjectManager::GetInstance().SetCamera(gCamera);
    gCamera->AddComponent<NPlayerController>();
    t->SetRotation(0.0f, 0.0f, 0.0f);

    //// create some cubes
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NCube>();
    //  auto t = g2->GetComponent<NTransform>();

    //  if (!m_rotatingObject)
    //  {
    //    m_rotatingObject = g2;
    //  }
    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 0.0f);
    //}

    // create terrain
    auto terrain = NGameObject::Instantiate<NTerrain>();
    terrain->GetComponent<NTransform>()->SetPosition(-50.0f, -2.0f, -30.0f);

	// create water
	auto water = NGameObject::Instantiate<NWater>();
	water->GetComponent<NTransform>()->SetPosition(-50.0f, 3.0f, -30.0f);

    //// create some cubes
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NCube>();
    //  auto m = g2->GetComponent<NMeshRenderer>();
    //  m->SetTexture(NPATH_TEXTURE_DEFAULT1);
    //  auto t = g2->GetComponent<NTransform>();
    //  
    //  t->SetScale(2.0f, 2.0f, 2.0f);
    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, -2.0f);
    //}

    //// create some cubes
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NCube>();
    //  auto m = g2->GetComponent<NMeshRenderer>();
    //  m->SetTexture(NPATH_TEXTURE_DEFAULT2);
    //  auto t = g2->GetComponent<NTransform>();
    //  t->SetScale(3.0f, 3.0f, 3.0f);
    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, -10.0f);
    //}

    //// create some spheres
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NTorus>();
    //  auto t = g2->GetComponent<NTransform>();
    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 10.0f);
    //}

    //// create some cones
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NCone>();
    //  auto t = g2->GetComponent<NTransform>();

    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 20.0f);
    //}

    //// create some Ikosader
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NIkosader>();
    //  auto t = g2->GetComponent<NTransform>();

    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 30.0f);
    //}

    //// create some Planes
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NPlane>();
    //  auto t = g2->GetComponent<NTransform>();

    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 40.0f);
    //}

    //// create some Torus
    //for (auto i = 1; i < 10; i++)
    //{
    //  auto g2 = NGameObject::Instantiate<NTorus>();
    //  auto t = g2->GetComponent<NTransform>();

    //  t->SetPosition(static_cast<float>(-i * 5), 0.0f, 50.0f);
    //}

    return true;
  }
  void NScene::Update(float a_deltaTime)
  {
 //   auto t = m_rotatingObject->GetComponent<NTransform>();
 //   rotationY += 0.001f;
 //   //t->SetRotation(0.0f, rotationY, 0.0f);
	//auto position = t->GetPosition();
	//position.x += t->GetUp().x * a_deltaTime * 0.1f;
	//position.y += t->GetUp().y * a_deltaTime * 0.1f;
	//position.z += t->GetUp().z * a_deltaTime * 0.1f;
	//t->SetPosition(position.x, position.y, position.z);

    NObjectManager::GetInstance().Update(a_deltaTime);
  }
  void NScene::Draw(IGraphics* a_renderer)
  {
    //a_renderer->SetFillMode(NFillMode::Wireframe);
    assert(a_renderer);
    // Set RenderPass
    // Terrain
    // Draw all terrain objects
    
    // Set Render Pass
    // GameObjects
    // Draw all gameobjects

    // Set RenderPass
    //a_renderer->DrawEverything();
    auto objects = NObjectManager::GetInstance().GetDrawableObjects();

    for (auto& obj : objects)
    {
      a_renderer->DrawGameobject(obj.second);
    }

    /*
       auto objects = NObjectManager::GetInstance().GetDrawableObjects();
    
    //// Select the correct type for calling the equal_range function
    //decltype(objects.equal_range("")) range;

    //// iterate through multimap's elements (by key)
    //for (auto i = objects.begin(); i != objects.end(); i = range.second)
    //{
    //  // Get the range of the current key
    //  range = objects.equal_range(i->first);

    //  // Now print out that whole range
    //  for (auto d = range.first; d != range.second; ++d)
    //  {
    //    // create instance buffer from objects
    //    std::cout << d->first << '\n';
    //  }
    //}

    //return;
    */

  }
  void NScene::Shutdown()
  {

  }
}
