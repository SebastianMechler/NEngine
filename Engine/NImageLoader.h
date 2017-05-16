#pragma once

#include "NImageData.h"

namespace Nully
{
  class NImageLoader
  {
  public:
    // For now a tga can only be loaded with following image specs: 32-Bits-Per-Pixel and UnmappedColorData 
    // IMPORTANT: call delete[] on a_imageData.data when done using the data, else memory leak
    static bool LoadTGA(const char* a_path, NImageData& a_imageData);
  };
}
