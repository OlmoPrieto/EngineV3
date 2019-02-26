#include "camera.h"

Camera::Camera() {

}

Camera::Camera(uint32_t render_width, uint32_t render_height) {
  float right = 1.0f;
  float left = -1.0f;
  float top = 1.0f;
  float bottom = -1.0f;

  float aspect_ratio = render_width / render_height;
  if (render_width > render_height) {
    aspect_ratio = render_width / render_height;
    right = render_width;
    left = 0.0f;
    top = render_height;
    bottom = 0.0f;
  }
  else {
    aspect_ratio = render_height / render_width;
    right = render_width;
    left = 0.0f;
    top = render_height;
    bottom = 0.0f;
  }

  float near = -1.0f;
  float far = 1.0f;
  float fov = 60.0f;

  m_projection_matrix.matrix[0] = 2.0f / (right - left);
  m_projection_matrix.matrix[1] = 0.0f;
  m_projection_matrix.matrix[2] = 0.0f;
  m_projection_matrix.matrix[3] = 0.0f;

  m_projection_matrix.matrix[4] = 0.0f;
  m_projection_matrix.matrix[5] = 2.0f / (top - bottom);
  m_projection_matrix.matrix[6] = 0.0f;
  m_projection_matrix.matrix[7] = 0.0f;

  m_projection_matrix.matrix[8] = 0.0f;
  m_projection_matrix.matrix[9] = 0.0f;
  m_projection_matrix.matrix[10] = -2.0f / (far - near);
  m_projection_matrix.matrix[11] = 0.0f;

  m_projection_matrix.matrix[12] = -(right + left) / (right - left);
  m_projection_matrix.matrix[13] = -(top + bottom) / (top - bottom);
  m_projection_matrix.matrix[14] = -(far + near) / (far - near);
  m_projection_matrix.matrix[15] = 1.0f;
}

Camera::~Camera() {

}

inline Camera::Type Camera::type() const {
  return m_type;
}

const Mat4& Camera::projectionMatrix() const {
  return m_projection_matrix;
}

const float* Camera::projectionMatrixData() const {
  return m_projection_matrix.matrix;
}
