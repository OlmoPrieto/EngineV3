#ifndef __UTILS_H__
#define __UTILS_H__

#include <chrono>
#include <cstdarg>
#include <cstdint>
#include <cstring>
#include <random>

#ifdef __PLATFORM_ANDROID__
  #include <android/log.h>
  static void printff(const char* format, ...) {
    va_list list;
    va_start(list, format);
    __android_log_print(ANDROID_LOG_INFO, "PONG-DX", format, va_arg(list, char*));
  }
#else
  static void printff(const char* format, ...) {
    va_list list;
    va_start(list, format);
    printf(format, va_arg(list, char*));
  }
#endif

static std::mt19937 g_random_generator;
static bool g_random_generator_seeded = false;
static int32_t RandomNumber(int32_t min = 0, int32_t max = 4294967296) {
  if (g_random_generator_seeded == false) {
      g_random_generator.seed(std::chrono::duration_cast<std::chrono::duration<int32_t > >(std::chrono::high_resolution_clock::now().time_since_epoch()).count());

      g_random_generator_seeded = true;
  }

  return min + (g_random_generator() % (max - min + 1));
}

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;

  Color() : r((uint8_t)255), g((uint8_t)255), b((uint8_t)255), a((uint8_t)255) {

  }

  Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a) {

  }

  void set(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) {
    r = _r; g = _g; b = _b; a = _a;
  }

  void setRandom() {
    r = (uint8_t)RandomNumber(0, 255);
    g = (uint8_t)RandomNumber(0, 255);
    b = (uint8_t)RandomNumber(0, 255);

    a = 255; // ??
  }

  static Color randomColor() {
    Color c;

    c.r = (uint8_t)RandomNumber(0, 255);
    c.g = (uint8_t)RandomNumber(0, 255);
    c.b = (uint8_t)RandomNumber(0, 255);

    if (c.r < 128) {
        c.r = 128;
    }
    if (c.g < 128) {
        c.g = 128;
    }
    if (c.b < 128) {
        c.b = 128;
    }

    c.a = 255; // ??

    return c;
  }
};

static void SetTextureColor(uint8_t* texture, uint32_t width, uint32_t height,
                            const Color& c, bool with_outline = false, uint32_t thickness = 1) {
//  uint32_t color = ((c.r << 24) & 0xFF000000) |
//    ((c.g << 24) & 0x00FF0000) |
//    ((c.b << 24) & 0x0000FF00) |
//    ((c.a << 24) & 0x000000FF);
//  //uint32_t color = (c.r << 24) | (c.g << 16) | (c.b << 8) | c.a;
//  memset(texture, color, width * height * 4);

  uint8_t* ptr = texture;
  for (uint32_t i = 0; i < width * height * 4; i += 4) {
    if (with_outline == true &&
      (i < width * thickness ||                         // upper border
      i > (width * height * 4) - (width * thickness) || // lower border
      i % width <= thickness - 1 ||                     // left border
      i % width - thickness >= width - thickness)) {    // right border

      *(ptr + 0) = 0;
      *(ptr + 1) = 0;
      *(ptr + 2) = 0;
      *(ptr + 3) = 0;
    }
    else {
      *(ptr + 0) = c.r;
      *(ptr + 1) = c.g;
      *(ptr + 2) = c.b;
      *(ptr + 3) = c.a;
    }
    ptr += 4;
  }
}

static void CreateCircleInTexture(uint8_t* texture, uint32_t width, uint32_t height, const Color& c) {
//    uint32_t color = ((c.r << 24) & 0xFF000000) |
//      ((c.g << 24) & 0x00FF0000) |
//      ((c.b << 24) & 0x0000FF00) |
//      ((c.a << 24) & 0x000000FF);

  memset(texture, 0, width * height * 4);

  uint32_t radius = (uint32_t)((float)width * 0.5f);
  uint32_t powered_radius = radius * radius;
  uint32_t x = 0;
  uint32_t y = 0;
  uint8_t* ptr = texture;
  //float inverse_width = 1 / width;
  for (uint32_t i = 0; i < width * height * 4; i += 4) {
    //x = (uint32_t)((i * 0.25f) * inverse_width);
    x = (uint32_t)((i * 0.25f) / width);
    y = (uint32_t)(i * 0.25f) % width;

    if ((x - radius) * (x - radius) + (y - radius) * (y - radius) < powered_radius) {
      *(ptr + 0) = c.r;
      *(ptr + 1) = c.g;
      *(ptr + 2) = c.b;
      *(ptr + 3) = c.a;
    }
    else {
      *(ptr + 0) = 0;
      *(ptr + 1) = 0;
      *(ptr + 2) = 0;
      *(ptr + 3) = 0;
    }

    ptr += 4;
  }
}

#endif // __UTILS_H__