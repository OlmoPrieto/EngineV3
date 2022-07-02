#include "Engine/attribute.h"

#include <cassert>

Attribute::Attribute(ValueType _eType, const std::string& _sName)
  : m_eType(_eType)
  , m_sName(_sName)
{
  switch (m_eType)
  {
    case ValueType::Invalid:
    case ValueType::Int1:
    case ValueType::Int2:
    case ValueType::Int3:
    case ValueType::Int4:
    {
      assert(false && "Not yet implemented");
      break;
    }
    case ValueType::Uint1:
    {
      m_pData = new uint32_t(0);
      break;
    }
    case ValueType::Uint2:
    case ValueType::Uint3:
    case ValueType::Uint4:
    {
      assert(false && "Not yet implemented");
      break;
    }
    case ValueType::Float1:
    {
      m_pData = new float(0.0f);
      break;
    }
    case ValueType::Float2:
    case ValueType::Float3:
    {
      m_pData = new Vec3();
      break;
    }
    case ValueType::Float4:
    case ValueType::Byte1:
    case ValueType::Byte2:
    case ValueType::Byte3:
    case ValueType::Byte4:
    case ValueType::Vec2:
    case ValueType::Vec3:
    case ValueType::Vec4:
    case ValueType::Mat2:
    case ValueType::Mat3:
    {
      assert(false && "Not yet implemented");
      break;
    }
    case ValueType::Mat4:
    {
      m_pData = new Mat4();
      break;
    }
    case ValueType::Texture:
    {
      m_pData = new std::shared_ptr<Texture>();
      break;
    }
    default:
    {
      assert(false && "Unhandled case");
      break;
    }
  }
}

Attribute::~Attribute()
{
  if (m_pData)
  {
    delete m_pData;
  }
}

// NOTE: gcc -> Specialization must be done outside class declaration
template <>
void Attribute::setValue<float>(const float& _fValue)
{
  *(float*)m_pData = _fValue;
}

template <>
void Attribute::setValue<uint32_t>(const uint32_t& _uValue)
{
  *(uint32_t*)m_pData = _uValue;
}

template <>
void Attribute::setValue<Mat4>(const Mat4& _mat4Value)
{
  *(Mat4*)m_pData = _mat4Value;
}

template <>
void Attribute::setValue<std::shared_ptr<Texture>>(const std::shared_ptr<Texture>& _oValue)
{
  *(std::shared_ptr<Texture>*)m_pData = _oValue;
}