#include "camera.h"

#include <cassert>

Camera::Camera() 
{

}

Camera::Camera(EType _eType, uint32_t _uRenderWidth, uint32_t _uRenderHeight) 
  : m_eType(_eType)
  , m_uRenderWidth(_uRenderWidth)
  , m_uRenderHeight(_uRenderHeight)
{
  switch (_eType)
  {
    case EType::Orthographic:
    {
      setProjectionToOrthographic();
      break;
    }
    case EType::Perspective:
    {
      assert(false && "Perspective camera mode not supported");
      break;
    }
    default:
    {
      printf("Unhandled camera mode\n");
    }
  }
}

Camera::~Camera() 
{

}

void Camera::setProjectionToOrthographic()
{
  float fRight = 1.0f;
  float fLeft = -1.0f;
  float fTop = 1.0f;
  float fBottom = -1.0f;

  float fAspectRatio = m_uRenderWidth / m_uRenderHeight;
  if (m_uRenderWidth > m_uRenderHeight) {
    fAspectRatio = m_uRenderWidth / m_uRenderHeight;
    fRight = m_uRenderWidth;
    fLeft = 0.0f;
    fTop = m_uRenderHeight;
    fBottom = 0.0f;
  }
  else {
    fAspectRatio = m_uRenderHeight / m_uRenderWidth;
    fRight = m_uRenderWidth;
    fLeft = 0.0f;
    fTop = m_uRenderHeight;
    fBottom = 0.0f;
  }

  float fNear = -1.0f;
  float fFar = 1.0f;
  float fFov = 60.0f;

  m_mat4ProjectionMatrix.matrix[0] = 2.0f / (fRight - fLeft);
  m_mat4ProjectionMatrix.matrix[1] = 0.0f;
  m_mat4ProjectionMatrix.matrix[2] = 0.0f;
  m_mat4ProjectionMatrix.matrix[3] = 0.0f;

  m_mat4ProjectionMatrix.matrix[4] = 0.0f;
  m_mat4ProjectionMatrix.matrix[5] = 2.0f / (fTop - fBottom);
  m_mat4ProjectionMatrix.matrix[6] = 0.0f;
  m_mat4ProjectionMatrix.matrix[7] = 0.0f;

  m_mat4ProjectionMatrix.matrix[8] = 0.0f;
  m_mat4ProjectionMatrix.matrix[9] = 0.0f;
  m_mat4ProjectionMatrix.matrix[10] = -2.0f / (fFar - fNear);
  m_mat4ProjectionMatrix.matrix[11] = 0.0f;

  m_mat4ProjectionMatrix.matrix[12] = -(fRight + fLeft) / (fRight - fLeft);
  m_mat4ProjectionMatrix.matrix[13] = -(fTop + fBottom) / (fTop - fBottom);
  m_mat4ProjectionMatrix.matrix[14] = -(fFar + fNear) / (fFar - fNear);
  m_mat4ProjectionMatrix.matrix[15] = 1.0f;
}

void Camera::render()
{

}