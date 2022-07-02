#pragma once

#include <cstdint>

#include "Engine/types.h"
#include "Engine/asset_manager.h"

class Texture : public Asset
{
public:
  enum class Type
  {
    Texture2D = 0,
    Cubemap
  };

  enum class Format
  {
    None = 0,
    R,
    RG,
    RGB,
    BGR,
    BGRA,
    RGBA,
    Depth,
    Depth32,
  };

  enum class Filter 
  {
    Nearest,
    Linear,
    NearestMipmapNearest,
    LinearMipmapNearest,
    NearestMipmapLinear,
    LinearMipmapLinear,
  };

  enum class Wrap
  {
    Repeat = 0,
    MirroredRepeat,
    ClampToEdge
  };

  Texture();
  ~Texture();

  // Texture
  void setFormat(Format _eFormat);
  void setMinFilter(Filter _eMinFilter) { m_eMinFilter = _eMinFilter; m_bReady = false; }
  void setMagFilter(Filter _eMagFilter) { m_eMagFilter = _eMagFilter; m_bReady = false; }
  void setWrapS(Wrap _eWrap) { m_eWrapS = _eWrap; m_bReady = false; }
  void setWrapT(Wrap _eWrap) { m_eWrapT = _eWrap; m_bReady = false; }
  void setWrapR(Wrap _eWrap) { m_eWrapR = _eWrap; m_bReady = false; }

  int32_t getInternalId() const { return m_iInternalId; }
  Type getType() const { return m_eType; }
  Format getFormat() const { return m_eFormat; }
  Filter getMinFilter() const { return m_eMinFilter; }
  Filter getMagFilter() const { return m_eMagFilter; }
  Wrap getWrapS() const { return m_eWrapS; }
  Wrap getWrapT() const { return m_eWrapT; }
  Wrap getWrapR() const { return m_eWrapR; }
  uint32_t getWidth() const { return m_uWidth; }
  uint32_t getHeight() const { return m_uHeight; }
  uint32_t getDepth() const { return m_uDepth; }
  uint32_t getTextureUnit() const { return m_uTextureUnit; }
  unsigned char* getData() const { return m_pData; }
  bool getGenerateMipMaps() const { return m_bGenerateMips; }
  
  bool getIsReady() const { return m_bReady; }

private:
  // Asset 
  bool load(const std::filesystem::path& _sPath) override;
  friend class AssetManager;
  friend class OpenGLImplementation;

  constexpr static bool m_sbFlipImagesOnLoad = true;

  std::filesystem::path m_sPath;
  byte* m_pData = nullptr;
  Type m_eType = Type::Texture2D;
  Format m_eFormat = Format::RGBA;
  Filter m_eMinFilter = Filter::Nearest;
  Filter m_eMagFilter = Filter::Linear;
  Wrap m_eWrapS = Wrap::Repeat;
  Wrap m_eWrapT = Wrap::Repeat;
  Wrap m_eWrapR = Wrap::Repeat;
  uint32_t m_uWidth = 0;
  uint32_t m_uHeight = 0;
  uint32_t m_uDepth = 0;
  uint32_t m_uTextureUnit = 0;
  int32_t m_iInternalId = -1;
  bool m_bReady = false;
  bool m_bGenerateMips = false;
};