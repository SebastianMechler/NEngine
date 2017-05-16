#include "NApplication.h"
#include "NScene.h" // main game scene
#include "NMemory.h"

using namespace Nully;

void main()
{
  NApplicationDesc applicationDesc = {};

  applicationDesc.windowDesc.width = 1024;
  applicationDesc.windowDesc.height = 768;
  applicationDesc.windowDesc.isFullScreen = false;
  applicationDesc.windowDesc.name = "Nully";
  applicationDesc.windowDesc.className = "NullyClass";

  applicationDesc.graphicsDesc.width = applicationDesc.windowDesc.width;
  applicationDesc.graphicsDesc.height = applicationDesc.windowDesc.height;
  applicationDesc.graphicsDesc.hwnd = 0;

  NSmartPtr<NScene> scene = new NScene();

  NApplication application;
  if (!application.Initialize(applicationDesc, NRenderer::DirectX11, scene.Get()))
  {
    return; // failed to init app
  }

  application.Run();
}