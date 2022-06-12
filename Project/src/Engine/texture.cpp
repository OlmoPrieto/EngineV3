#include "Engine/texture.h"

#include <cassert>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

Texture::Texture()
{

}

Texture::~Texture()
{
  if (m_pData)
  {
    stbi_image_free(m_pData);
  }
}

void Texture::setFormat(Format _eFormat)
{
  m_eFormat = _eFormat;

  switch (_eFormat)
  {
    case Texture::Format::None:
    {
      assert(false && "Texture format None specified");
      break;
    }
    case Texture::Format::R:
    {
      m_uDepth = 1;
      break;
    }
    case Texture::Format::RG:
    {
      m_uDepth = 2;
      break;
    }
    case Texture::Format::RGB:
    {
      m_uDepth = 3;
      break;
    }
    case Texture::Format::BGR:
    {
      m_uDepth = 3;
      break;
    }
    case Texture::Format::BGRA:
    {
      break;
    }
    case Texture::Format::RGBA:
    {
      m_uDepth = 4;
      break;
    }
    case Texture::Format::Depth:
    {
      m_uDepth = 1;
      break;
    }
    case Texture::Format::Depth32:
    {
      m_uDepth = 1;
      break;
    }
    default:
    {
      assert(false && "Format not supported");
      break;
    }
  }

  m_bReady = false;
}

bool Texture::load(const std::filesystem::path& _sPath)
{
  m_sPath = _sPath;

  // Basic usage (see HDR discussion below for HDR usage):
//    int x,y,n;
//    unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
//    // ... process data if not NULL ...
//    // ... x = width, y = height, n = # 8-bit components per pixel ...
//    // ... replace '0' with '1'..'4' to force that many components per pixel
//    // ... but 'n' will always be the number that it would have been if you said 0
//    stbi_image_free(data)

  int32_t iWidth;
  int32_t iHeight;
  int32_t iDepth;
  stbi_set_flip_vertically_on_load(m_sbFlipImagesOnLoad);
  m_pData = stbi_load(m_sPath.relative_path().string().c_str(), &iWidth, &iHeight, &iDepth, 0);
  if (!m_pData)
    return false;

  m_uWidth = (uint32_t)iWidth;
  m_uHeight = (uint32_t)iHeight;
  m_uDepth = (uint32_t)iDepth;

  return true;
}