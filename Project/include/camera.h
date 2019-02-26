#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "maths.h"
#include "utils.h"

class Camera {
public:
  enum class Type {
    Orthographic = 0,
    Perspective
  };

  Camera(uint32_t render_width, uint32_t render_height);
  ~Camera();

  inline Type type() const;
  const Mat4& projectionMatrix() const;
  const float* projectionMatrixData() const;

  void setClearColor(const Color& color);
  void setClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
  void setClearColor(float r, float g, float b, float a);

private:
  Camera();

  Mat4 m_projection_matrix;
  Type m_type = Type::Orthographic;
  Color m_clear_color;
};

#endif  // __CAMERA_H__
