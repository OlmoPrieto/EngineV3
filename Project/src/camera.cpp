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
      setProjectionToPerspective();
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
  float fRight  =  (float)m_uRenderWidth  * 0.5f;
  float fLeft   = -(float)m_uRenderWidth  * 0.5f;
  float fTop    =  (float)m_uRenderHeight * 0.5f;
  float fBottom = -(float)m_uRenderHeight * 0.5f;

  float fAspectRatio = (float)m_uRenderWidth / (float)m_uRenderHeight;

  float fNear = 0.1f;
  float fFar = 100.0f;
  float fFov = 60.0f;

  m_mat4ProjectionMatrix.matrix[0] = 2.0f / (fRight - fLeft);
  m_mat4ProjectionMatrix.matrix[1] = 0.0f;
  m_mat4ProjectionMatrix.matrix[2] = 0.0f;
  m_mat4ProjectionMatrix.matrix[3] = -(fRight + fLeft) / (fRight - fLeft);

  m_mat4ProjectionMatrix.matrix[4] = 0.0f;
  m_mat4ProjectionMatrix.matrix[5] = 2.0f / (fTop - fBottom);
  m_mat4ProjectionMatrix.matrix[6] = 0.0f;
  m_mat4ProjectionMatrix.matrix[7] = -(fTop + fBottom) / (fTop - fBottom);

  m_mat4ProjectionMatrix.matrix[8] = 0.0f;
  m_mat4ProjectionMatrix.matrix[9] = 0.0f;
  m_mat4ProjectionMatrix.matrix[10] = -2.0f / (fFar - fNear);
  m_mat4ProjectionMatrix.matrix[11] = -(fFar + fNear) / (fFar - fNear);

  m_mat4ProjectionMatrix.matrix[12] = 0.0f;
  m_mat4ProjectionMatrix.matrix[13] = 0.0f;
  m_mat4ProjectionMatrix.matrix[14] = 0.0f;
  m_mat4ProjectionMatrix.matrix[15] = 1.0f;
}

void Camera::setProjectionToPerspective()
{
  // ??? https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix
  // not tested https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/opengl-perspective-projection-matrix

  float fNear = 0.1f;
  float fFar = 100.0f;
  float fFov = 60.0f;

  float fAspectRatio = (float)m_uRenderWidth / (float)m_uRenderHeight;

  float fScale = tan((fFov * 0.5f * 3.14159f) / 180.0f) * fNear;
  float fRight = fAspectRatio * fScale;
  float fLeft = -fRight;
  float fTop = fScale;
  float fBottom = -fTop;

  m_mat4ProjectionMatrix.matrix[0]  = (2.0f * fNear) / (fRight - fLeft);
  m_mat4ProjectionMatrix.matrix[5]  = (2.0f * fNear) / (fTop - fBottom);
  m_mat4ProjectionMatrix.matrix[10] = -((fFar + fNear) / (fFar - fNear));
  m_mat4ProjectionMatrix.matrix[15] = 0.0f;
  m_mat4ProjectionMatrix.matrix[8]  = (fRight + fLeft) / (fRight - fLeft);
  m_mat4ProjectionMatrix.matrix[9]  = (fTop + fBottom) / (fTop - fBottom);
  m_mat4ProjectionMatrix.matrix[11] = -1.0f;
  m_mat4ProjectionMatrix.matrix[14] = -((2.0f * fFar * fNear) / (fFar - fNear));


  // https://learnopengl.com/Getting-started/Camera
  // https://stackoverflow.com/questions/349050/calculating-a-lookat-matrix
  Vec3 vec3Pos(0.0f, 0.0f, 3.0f);
  Vec3 vec3Target(0.0f, 0.0f, 0.0f);
  //Vec3 vec3ZAxis = Vec3::normalize(vec3Target - vec3Pos); // direction
  Vec3 vec3ZAxis = Vec3::normalize(vec3Pos - vec3Target); // direction
  Vec3 vec3Up(0.0f, 1.0f, 0.0f);
  Vec3 vec3XAxis = Vec3::normalize(vec3Up.cross(vec3ZAxis));
  Vec3 vec3YAxis = vec3ZAxis.cross(vec3XAxis);

  m_mat4ViewMatrix.matrix[3]  = -vec3Pos.x;
  m_mat4ViewMatrix.matrix[7]  = -vec3Pos.y;
  m_mat4ViewMatrix.matrix[11] = -vec3Pos.z;

  Mat4 mat4Rotation;
  mat4Rotation.matrix[0] = vec3XAxis.x;
  mat4Rotation.matrix[1] = vec3XAxis.y;
  mat4Rotation.matrix[2] = vec3XAxis.z;

  mat4Rotation.matrix[4] = vec3YAxis.x;
  mat4Rotation.matrix[5] = vec3YAxis.y;
  mat4Rotation.matrix[6] = vec3YAxis.z;

  mat4Rotation.matrix[8]  = vec3ZAxis.x;
  mat4Rotation.matrix[9]  = vec3ZAxis.y;
  mat4Rotation.matrix[10] = vec3ZAxis.z;

  m_mat4ViewMatrix = mat4Rotation * m_mat4ViewMatrix;
}
