#pragma once

#include <string>
#include <cassert>

#include "maths.h"
#include "texture.h"

//
enum class ValueType
{
  Invalid = 0,

  Int1,
  Int2,
  Int3,
  Int4,
  
  Uint1,
  Uint2,
  Uint3,
  Uint4,

  Float1,
  Float2,
  Float3,
  Float4,

  Byte1,
  Byte2,
  Byte3,
  Byte4,

  Vec2,
  Vec3,
  Vec4,

  Mat2,
  Mat3,
  Mat4,

  Texture,

  Int = Int1,
  Uint = Uint1,
  Float = Float1,
  Byte = Byte1
};
//

class Attribute
{
public:
  Attribute(ValueType _eType, const std::string& _sName); // Allocs for memory
  ~Attribute(); // Releases memory

  virtual const std::string& getName() const { return m_sName; }
  ValueType getType() const { return m_eType; }
  bool getIsReady() const { return m_bDirty; }

  template <class T>
  void setValue(const T& _oT) { assert(false); }

  //

  template <class T>
  T* getData() const { return (T*)m_pData; }

protected:
  std::string m_sName;
  void* m_pData = nullptr;
  ValueType m_eType = ValueType::Invalid;
  bool m_bDirty = true;
};