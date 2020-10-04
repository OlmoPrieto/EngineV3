#include "texture.h"

#include <cassert>

Texture::Texture(uint32_t _uWidth, uint32_t _uHeight, uint32_t _uDepth, Format _eFormat, Type _eType)
  : m_uWidth(_uWidth)
  , m_uHeight(_uHeight)
  , m_uDepth(_uDepth)
  , m_eFormat(_eFormat)
  , m_eType(_eType)
{

}

Texture::~Texture()
{

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
