#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "maths.h"
#include "utils.h"

class Camera {
public:
  enum class EType 
  {
    Orthographic = 0,
    Perspective
  };

  Camera(EType _eType, uint32_t _uRenderWidth, uint32_t _uRenderHeight);
  ~Camera();

  EType getType() const { return m_eType; }
  const Mat4& getProjectionMatrix() const { return m_mat4ProjectionMatrix; }
  const float* getProjectionMatrixData() const { return m_mat4ProjectionMatrix.matrix; }

  void setClearColor(const Color& color);
  void setClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void setClearColor(float r, float g, float b, float a);

  void setProjectionToOrthographic();

private:
  Camera();

  void render();

  Mat4 m_mat4ProjectionMatrix;
  EType m_eType = EType::Orthographic;
  Color m_oClearColor;
  uint32_t m_uRenderWidth = 0;
  uint32_t m_uRenderHeight = 0;
  bool m_bEnabled = true;
};

#endif  // __CAMERA_H__
