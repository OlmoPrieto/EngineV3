#ifndef __SPRITE_H__
#define __SPRITE_H__

#ifdef __PLATFORM_MACOSX__
  #include <OpenGL/gl3.h>
#elif __PLATFORM_LINUX__
  #include <glew/include/GL/glew.h>
#elif __PLATFORM_WINDOWS__
  #include <glew/include/GL/glew.h>
#elif __PLATFORM_ANDROID__
  #include <GLES2/gl2.h>
#endif

#include "Engine/maths.h"
#include "Engine/utils.h"

class Sprite {
public:

  Sprite();
  ~Sprite();

  Color getColor() const;
  Vec2 getPosition() const;
  Vec2 getScale() const;

  void setColor(const Color& color);  // The color is the tint (used in the shader)
  void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);  // The color is the tint (used in the shader)
  void setPosition(const Vec2& position);
  void setPosition(float x, float y);
  void setPositionX(float x);
  void setPositionY(float y);
  void setScale(const Vec2& scale);
  void setScale(float x, float y);
  void setScaleX(float x);
  void setScaleY(float y);

  void setTextureData(uint8_t* data);

  uint32_t getTextureHandler() const;
  uint8_t* getTextureData();
  uint32_t getTextureWidth() const;
  uint32_t getTextureHeight() const;

  // public variables
  Vec2 m_position;
  Vec2 m_scale;
  Color m_color;  // m_color is now used as tint in the shader

  uint32_t m_texture_width = 0;
  uint32_t m_texture_height = 0;

private:
  struct OpenGLData {
    GLuint m_texture_id = 0;
  };

  OpenGLData m_opengl_data;

  uint8_t* m_texture = nullptr;
};

#endif //__SPRITE_H__
