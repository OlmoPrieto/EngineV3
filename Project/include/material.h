#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "shader.h"

#include <memory>
#include <string>
#include <vector>

class Material {
public:
  Material();
  ~Material();

  inline std::string getName() const;

private:
  std::vector<std::weak_ptr<Shader>> m_vShaders;
  std::string m_sName;
};

#endif  // __MATERIAL_H__
