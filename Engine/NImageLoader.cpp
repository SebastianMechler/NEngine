#include "NImageLoader.h"

#include "NImageTGAHeader.h"
#include "NFile.h"
#include "NMemory.h"
#include "NTools.h"

namespace Nully
{
  bool NImageLoader::LoadTGA(const char* a_path, NImageData& a_imageData)
  {
    NFile file;
    if (file.Open(a_path, NFileMode::Read) != NResult::Success)
    {
      // could not open file
      return false;
    }

    auto size = file.GetFileSize(a_path);
    if (size == 0)
    {
      // fileSize is 0
      return false;
    }

    // create temp buffer for header
    NImageTGAHeader tgaHeader{};

    // read header
    file.Read(&tgaHeader, sizeof(NImageTGAHeader));
    
    if (tgaHeader.bitsPerPixel != 32 && tgaHeader.bitsPerPixel != 24)
    {
      // 32 bit and 24 bit only allowed
      return false;
    }

    if (tgaHeader.imageType != NImageTGAType::COLOR_UNMAPPED)
    {
      // only uncompressed and color without mapping allowed
      return false;
    }
  
    // create raw image data
    uint8_t* rawImage = new uint8_t[size - sizeof(NImageTGAHeader)];
    if (!rawImage)
    {
      // failed to allocate space
      return false;
    }

    if (file.Read(rawImage, size - sizeof(NImageTGAHeader)) != NResult::Success)
    {
      // failed to read file
      return false;
    }

    uint32_t imgDesc = static_cast<uint32_t>(tgaHeader.imageDescriptor);

    // This only works correctly on Intel CPU, cause AMD Memory storage is switched...
    if (NTools::IsBitSet(imgDesc, 4) && !NTools::IsBitSet(imgDesc, 5))
    {
      // tga is topLeft

      // Format is BGR or BGRA on Intel, depending on bitsPerPixel

      // we can assign the values
      a_imageData.data = rawImage;
      a_imageData.width = tgaHeader.width;
      a_imageData.height = tgaHeader.height;
      a_imageData.bitsPerPixel = tgaHeader.bitsPerPixel;
      return true;
    }

    // topLeft is not set, image was not exported with correct settings
    return false;
  }
}
