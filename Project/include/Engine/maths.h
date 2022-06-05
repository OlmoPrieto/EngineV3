#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <cmath>
 
namespace utils 
{
// ========================================================
static int32_t Min(int32_t a, int32_t b) 
{
  return a < b ? a : b;
}

static int32_t Max(int32_t a, int32_t b) 
{
  return a > b ? a : b;
}

static float Lerp(float a, float b, float alpha) 
{
  return a + alpha * (b - a);
}
} // namespace utils
// ========================================================
// ========================================================
struct Vec2 
{
  float x;
  float y;

  Vec2() : x(0.0f), y(0.0f) 
  {

  }

  Vec2(float x_, float y_) : x(x_), y(y_) 
  {

  }

  Vec2(const Vec2& other) 
  {
    x = other.x; y = other.y;
  }

  Vec2& operator = (const Vec2& other) 
  {
    x = other.x; y = other.y;
    return *this;
  }

  Vec2& operator += (const Vec2& other) 
  {
    x += other.x; y += other.y;
    return *this;
  }

  Vec2& operator *= (const Vec2& other) 
  {
    x *= other.x; y *= other.y;
    return *this;
  }

  Vec2 operator * (const Vec2& other) 
  {
    Vec2 r(*this);
    r.x *= other.x; r.y *= other.y;
    return r;
  }

  Vec2 operator + (const Vec2& other) 
  {
    Vec2 r(*this);
    r.x += other.x; r.y += other.y;
    return r;
  }

  Vec2 operator - (const Vec2& other) 
  {
    Vec2 r(*this);
    r.x -= other.x; r.y -= other.y;
    return r;
  }

  Vec2& operator *= (float a) 
  {
    x *= a; y *= a;
    return *this;
  }

  Vec2 operator * (float a) 
  {
    Vec2 r(*this);
    r.x *= a; r.y *= a;
    return r;
  }

  bool operator == (float a) 
  {
    if (x == a && y == a) {
      return true;
    }

    return false;
  }

  bool operator != (float a) 
  {
    return !operator==(a);
  }

};
// ========================================================
// ========================================================
struct Vec3 
{
  float x;
  float y;
  float z;

  Vec3() : x(0.0f), y(0.0f), z(0.0f) 
  {

  }

  Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) 
  {

  }

  Vec3(const Vec3& other) 
  {
    x = other.x; y = other.y; z = other.z;
  }

  Vec3(const Vec2& other, float z_) 
  {
    x = other.x; y = other.y; z = z_;
  }

  void Vec3::set(float _fX, float _fY, float _fZ)
  {
    x = _fX; y = _fY; z = _fZ;
  }

  Vec3& operator = (const Vec3& other) 
  {
    x = other.x; y = other.y; z = other.z;
    return *this;
  }

  Vec3& operator += (const Vec3& other) 
  {
    x += other.x; y += other.y; z += other.z;
    return *this;
  }

  Vec3& operator *= (const Vec3& other)
  {
    x *= other.x; y *= other.y; z *= other.z;
    return *this;
  }

  Vec3 operator * (const Vec3& other) 
  {
    Vec3 r(*this);
    r.x *= other.x; r.y *= other.y; r.z *= other.z;
    return r;
  }

  Vec3& operator *= (float a) 
  {
    x *= a; y *= a; z *= a;
    return *this;
  }

  Vec3 operator * (float a) 
  {
    Vec3 r(*this);
    r.x *= a; r.y *= a; r.z *= a;
    return r;
  }

  Vec3 operator + (const Vec3& other)
  {
    Vec3 r(*this);
    r.x += other.x; r.y += other.y; r.z += other.z;
    return r;
  }

  Vec3 operator - (const Vec3& other)
  {
    Vec3 r(*this);
    r.x -= other.x; r.y -= other.y; r.z -= other.z;
    return r;
  }

  Vec3 cross(const Vec3& other)
  {
    Vec3 r;
    r.x = y * other.z - z * other.y;
    //r.y = -(x * other.z - z * other.x);
    r.y = z * other.x - x * other.z;
    r.z = x * other.y - y * other.x;

    return r;
  }

  void normalize()
  {
    float fLenght = sqrt((x * x) + (y * y) + (z * z));
    x /= fLenght;
    y /= fLenght;
    z /= fLenght;
  }

  static Vec3 normalize(const Vec3& _vec3Other)
  {
    Vec3 vec3Result = _vec3Other;
    vec3Result.normalize();
    return vec3Result;
  }

};
// ========================================================
// ========================================================
struct Mat4 
{
  float matrix[16];

  Mat4() 
  {
    setIdentity();
  }

  ~Mat4() 
  {

  }

  void setIdentity() 
  {
    memset(matrix, 0, sizeof(float) * 16);
    matrix[0]  = 1.0f;
    matrix[5]  = 1.0f;
    matrix[10] = 1.0f;
    matrix[15] = 1.0f;
  }

  void setToZero()
  {
    memset(matrix, 0, sizeof(float) * 16);
  }

  void inverse()
  {
    // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix

    float inv[16];
    float det = 0.0f;

    inv[0] = matrix[5] * matrix[10] * matrix[15] -
      matrix[5] * matrix[11] * matrix[14] -
      matrix[9] * matrix[6] * matrix[15] +
      matrix[9] * matrix[7] * matrix[14] +
      matrix[13] * matrix[6] * matrix[11] -
      matrix[13] * matrix[7] * matrix[10];

    inv[4] = -matrix[4] * matrix[10] * matrix[15] +
      matrix[4] * matrix[11] * matrix[14] +
      matrix[8] * matrix[6] * matrix[15] -
      matrix[8] * matrix[7] * matrix[14] -
      matrix[12] * matrix[6] * matrix[11] +
      matrix[12] * matrix[7] * matrix[10];

    inv[8] = matrix[4] * matrix[9] * matrix[15] -
      matrix[4] * matrix[11] * matrix[13] -
      matrix[8] * matrix[5] * matrix[15] +
      matrix[8] * matrix[7] * matrix[13] +
      matrix[12] * matrix[5] * matrix[11] -
      matrix[12] * matrix[7] * matrix[9];

    inv[12] = -matrix[4] * matrix[9] * matrix[14] +
      matrix[4] * matrix[10] * matrix[13] +
      matrix[8] * matrix[5] * matrix[14] -
      matrix[8] * matrix[6] * matrix[13] -
      matrix[12] * matrix[5] * matrix[10] +
      matrix[12] * matrix[6] * matrix[9];


    det = matrix[0] * inv[0] + matrix[1] * inv[4] + matrix[2] * inv[8] + matrix[3] * inv[12];

    if (det == 0.0f)
    {
      assert(false && "det == 0");
      return;
    }


    inv[1] = -matrix[1] * matrix[10] * matrix[15] +
      matrix[1] * matrix[11] * matrix[14] +
      matrix[9] * matrix[2] * matrix[15] -
      matrix[9] * matrix[3] * matrix[14] -
      matrix[13] * matrix[2] * matrix[11] +
      matrix[13] * matrix[3] * matrix[10];

    inv[5] = matrix[0] * matrix[10] * matrix[15] -
      matrix[0] * matrix[11] * matrix[14] -
      matrix[8] * matrix[2] * matrix[15] +
      matrix[8] * matrix[3] * matrix[14] +
      matrix[12] * matrix[2] * matrix[11] -
      matrix[12] * matrix[3] * matrix[10];

    inv[9] = -matrix[0] * matrix[9] * matrix[15] +
      matrix[0] * matrix[11] * matrix[13] +
      matrix[8] * matrix[1] * matrix[15] -
      matrix[8] * matrix[3] * matrix[13] -
      matrix[12] * matrix[1] * matrix[11] +
      matrix[12] * matrix[3] * matrix[9];

    inv[13] = matrix[0] * matrix[9] * matrix[14] -
      matrix[0] * matrix[10] * matrix[13] -
      matrix[8] * matrix[1] * matrix[14] +
      matrix[8] * matrix[2] * matrix[13] +
      matrix[12] * matrix[1] * matrix[10] -
      matrix[12] * matrix[2] * matrix[9];

    inv[2] = matrix[1] * matrix[6] * matrix[15] -
      matrix[1] * matrix[7] * matrix[14] -
      matrix[5] * matrix[2] * matrix[15] +
      matrix[5] * matrix[3] * matrix[14] +
      matrix[13] * matrix[2] * matrix[7] -
      matrix[13] * matrix[3] * matrix[6];

    inv[6] = -matrix[0] * matrix[6] * matrix[15] +
      matrix[0] * matrix[7] * matrix[14] +
      matrix[4] * matrix[2] * matrix[15] -
      matrix[4] * matrix[3] * matrix[14] -
      matrix[12] * matrix[2] * matrix[7] +
      matrix[12] * matrix[3] * matrix[6];

    inv[10] = matrix[0] * matrix[5] * matrix[15] -
      matrix[0] * matrix[7] * matrix[13] -
      matrix[4] * matrix[1] * matrix[15] +
      matrix[4] * matrix[3] * matrix[13] +
      matrix[12] * matrix[1] * matrix[7] -
      matrix[12] * matrix[3] * matrix[5];

    inv[14] = -matrix[0] * matrix[5] * matrix[14] +
      matrix[0] * matrix[6] * matrix[13] +
      matrix[4] * matrix[1] * matrix[14] -
      matrix[4] * matrix[2] * matrix[13] -
      matrix[12] * matrix[1] * matrix[6] +
      matrix[12] * matrix[2] * matrix[5];

    inv[3] = -matrix[1] * matrix[6] * matrix[11] +
      matrix[1] * matrix[7] * matrix[10] +
      matrix[5] * matrix[2] * matrix[11] -
      matrix[5] * matrix[3] * matrix[10] -
      matrix[9] * matrix[2] * matrix[7] +
      matrix[9] * matrix[3] * matrix[6];

    inv[7] = matrix[0] * matrix[6] * matrix[11] -
      matrix[0] * matrix[7] * matrix[10] -
      matrix[4] * matrix[2] * matrix[11] +
      matrix[4] * matrix[3] * matrix[10] +
      matrix[8] * matrix[2] * matrix[7] -
      matrix[8] * matrix[3] * matrix[6];

    inv[11] = -matrix[0] * matrix[5] * matrix[11] +
      matrix[0] * matrix[7] * matrix[9] +
      matrix[4] * matrix[1] * matrix[11] -
      matrix[4] * matrix[3] * matrix[9] -
      matrix[8] * matrix[1] * matrix[7] +
      matrix[8] * matrix[3] * matrix[5];

    inv[15] = matrix[0] * matrix[5] * matrix[10] -
      matrix[0] * matrix[6] * matrix[9] -
      matrix[4] * matrix[1] * matrix[10] +
      matrix[4] * matrix[2] * matrix[9] +
      matrix[8] * matrix[1] * matrix[6] -
      matrix[8] * matrix[2] * matrix[5];

    det = 1.0f / det;

    for (unsigned int i = 0; i < 16; ++i)
      matrix[i] = inv[i] * det;
  }

  void operator =(const Mat4& other) 
  {
    matrix[0] = other.matrix[0];  matrix[1] = other.matrix[1];  matrix[2] = other.matrix[2];  matrix[3] = other.matrix[3];
    matrix[4] = other.matrix[4];  matrix[5] = other.matrix[5];  matrix[6] = other.matrix[6];  matrix[7] = other.matrix[7];
    matrix[8] = other.matrix[8];  matrix[9] = other.matrix[9];  matrix[10] = other.matrix[10]; matrix[11] = other.matrix[11];
    matrix[12] = other.matrix[12]; matrix[13] = other.matrix[13]; matrix[14] = other.matrix[14]; matrix[15] = other.matrix[15];
  }

  Mat4 operator *(const Mat4& other) const
  {
    Mat4 result;
    result.matrix[0] = matrix[0] * other.matrix[0] + matrix[1] * other.matrix[4] + matrix[2] * other.matrix[8] + matrix[3] * other.matrix[12];
    result.matrix[1] = matrix[0] * other.matrix[1] + matrix[1] * other.matrix[5] + matrix[2] * other.matrix[9] + matrix[3] * other.matrix[13];
    result.matrix[2] = matrix[0] * other.matrix[2] + matrix[1] * other.matrix[6] + matrix[2] * other.matrix[10] + matrix[3] * other.matrix[14];
    result.matrix[3] = matrix[0] * other.matrix[3] + matrix[1] * other.matrix[7] + matrix[2] * other.matrix[11] + matrix[3] * other.matrix[15];

    result.matrix[4] = matrix[4] * other.matrix[0] + matrix[5] * other.matrix[4] + matrix[6] * other.matrix[8] + matrix[7] * other.matrix[12];
    result.matrix[5] = matrix[4] * other.matrix[1] + matrix[5] * other.matrix[5] + matrix[6] * other.matrix[9] + matrix[7] * other.matrix[13];
    result.matrix[6] = matrix[4] * other.matrix[2] + matrix[5] * other.matrix[6] + matrix[6] * other.matrix[10] + matrix[7] * other.matrix[14];
    result.matrix[7] = matrix[4] * other.matrix[3] + matrix[5] * other.matrix[7] + matrix[6] * other.matrix[11] + matrix[7] * other.matrix[15];

    result.matrix[8]  = matrix[8] * other.matrix[0] + matrix[9] * other.matrix[4] + matrix[10] * other.matrix[8] + matrix[11] * other.matrix[12];
    result.matrix[9]  = matrix[8] * other.matrix[1] + matrix[9] * other.matrix[5] + matrix[10] * other.matrix[9] + matrix[11] * other.matrix[13];
    result.matrix[10] = matrix[8] * other.matrix[2] + matrix[9] * other.matrix[6] + matrix[10] * other.matrix[10] + matrix[11] * other.matrix[14];
    result.matrix[11] = matrix[8] * other.matrix[3] + matrix[9] * other.matrix[7] + matrix[10] * other.matrix[11] + matrix[11] * other.matrix[15];

    result.matrix[12] = matrix[12] * other.matrix[0] + matrix[13] * other.matrix[4] + matrix[14] * other.matrix[8] + matrix[15] * other.matrix[12];
    result.matrix[13] = matrix[12] * other.matrix[1] + matrix[13] * other.matrix[5] + matrix[14] * other.matrix[9] + matrix[15] * other.matrix[13];
    result.matrix[14] = matrix[12] * other.matrix[2] + matrix[13] * other.matrix[6] + matrix[14] * other.matrix[10] + matrix[15] * other.matrix[14];
    result.matrix[15] = matrix[12] * other.matrix[3] + matrix[13] * other.matrix[7] + matrix[14] * other.matrix[11] + matrix[15] * other.matrix[15];

    return result;
  }

  void operator *=(const Mat4& other) 
  {
    *this = *this * other;
  }

  void transpose()
  {
    for (uint32_t i = 0; i < 4; ++i)
    {
      for (uint32_t j = 0; j < 4; ++j)
      {
        float fTemp = matrix[i * 4 + j];
        matrix[i * 4 + j] = matrix[j * 4 + i];
        matrix[j * 4 + i] = fTemp;
      }
    }
  }

  void setPosition(float _fX, float _fY, float _fZ)
  {
    matrix[12] = _fX;
    matrix[13] = _fY;
    matrix[14] = _fZ;
	
	  /*matrix[3] = _fX;
    matrix[7] = _fY;
    matrix[11] = _fZ;*/
  }

  void setPosition(const Vec3& _vec3Position)
  {
    setPosition(_vec3Position.x, _vec3Position.y, _vec3Position.z);
  }

  void setScale(float _fX, float _fY, float _fZ)
  {
    matrix[0] = _fX;
    matrix[5] = _fY;
    matrix[10] = _fZ;
  }

  void setScale(const Vec3& _vec3Scale)
  {
    setScale(_vec3Scale.x, _vec3Scale.y, _vec3Scale.z);
  }

  void print()
  {
    for (uint32_t i = 0; i < 4; ++i)
    {
      for (uint32_t j = 0; j < 4; ++j)
      {
        printf("%.6f\t", matrix[i + (j * 4)]);
      }
      printf("\n");
    }
    printf("\n\n\n");
  }
};
// ========================================================