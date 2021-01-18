// image.cc

#include "lime.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

namespace lime {
   namespace image {
      using uint8  = unsigned char;
      using uint16 = unsigned short;
      using uint32 = unsigned int;

      using int32  = signed int;

#pragma pack(push, 1)
      struct BMPHeader {
         uint8  magic_[2];
         uint32 ignored_[2];
         uint32 offset_;
      };

      struct DIBHeader {
         uint32 size_;
         uint32 width_;
         uint32 height_;
         uint16 planes_;
         uint16 bits_per_pixel_;
         uint32 compression_;
         uint32 image_size_;
         uint32 horizontal_resolution_;
         uint32 vertical_resolution_;
         uint32 color_count_;
         uint32 important_color_count_;
      };
#pragma pack(pop)

      namespace {
         template <typename Fn>
         struct scope_guard {
            scope_guard(Fn f) : fn(f) { }
            ~scope_guard() { fn(); }
            Fn fn;
         };

         template <typename Fn>
         scope_guard<Fn> make_scope_guard(Fn f) {
            return scope_guard<Fn>(f);
         }
      } // !anon

      bool load_file_content(const char *filename, std::vector<uint8> &content)
      {
         HANDLE handle = CreateFileA(filename,
                                     GENERIC_READ,
                                     FILE_SHARE_READ,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL,
                                     NULL);
         if (handle == INVALID_HANDLE_VALUE) {
            return false;
         }

         auto defer = make_scope_guard(([&]() {
            CloseHandle(handle);
         }));

         LARGE_INTEGER size = {};
         if (!GetFileSizeEx(handle, &size)) {
            return false;
         }

         content.resize(size.QuadPart);
         if (!ReadFile(handle, content.data(), size.LowPart, NULL, NULL)) {
            return false;
         }

         if (size.HighPart > 0) {
            if (!ReadFile(handle, content.data() + size.LowPart, size.HighPart, NULL, NULL)) {
               return false;
            }
         }

         return true;
      }

      bool create(const char *filename, bitmap &image)
      {
         std::vector<uint8> content;
         if (!load_file_content(filename, content)) {
            return false;
         }

         const uint8 *at = content.data();
         BMPHeader *bmp = (BMPHeader *)at;
         at += sizeof(BMPHeader);
         if (bmp->magic_[0] != 'B' && bmp->magic_[1] != 'M') {
            return false;
         }

         DIBHeader *dib = (DIBHeader *)at;
         at = content.data() + bmp->offset_;
         if (dib->bits_per_pixel_ != 24 && dib->bits_per_pixel_ != 32) {
            return false;
         }

         if (dib->compression_ != 0 && dib->compression_ != 3) {
            return false;
         }

         const int32 bytes_per_pixel = dib->bits_per_pixel_ / 8;
         if (bytes_per_pixel != 3 && bytes_per_pixel != 4) {
            return false;
         }

         const int32 width = dib->width_;
         const int32 height = dib->height_;
         const int32 stride = width * bytes_per_pixel;
         const uint8 *src = at + (height - 1) * stride;

         color *data = new color[width * height];
         for (int32 y = 0; y < height; y++) {
            color *dst = data + y * width;

            for (int32 x = 0; x < width; x++) {
               const int32 index = x * bytes_per_pixel;
               const uint32 r = src[index + 2];
               const uint32 b = src[index + 0];
               const uint32 g = src[index + 1];
               uint32 a = 0xff;

               if (bytes_per_pixel == 4) {
                  a = src[index + 3];
               }

               color rgba = {};
               rgba.r = r & 0xff;
               rgba.g = g & 0xff;
               rgba.b = b & 0xff;
               rgba.a = a & 0xff;
               *dst++ = rgba;
            }

            src -= stride;
         }

         image.width  = width;
         image.height = height;
         image.data   = data;

         return true;
      }

      void destroy(bitmap &image)
      {
         if (image.data) {
            delete[] image.data;
         }

         image.width = 0;
         image.height = 0;
         image.data = nullptr;
      }
   } // !image
} // !lime
