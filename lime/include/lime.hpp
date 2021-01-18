// lime.hpp

#ifndef LIME_HPP_INCLUDED
#define LIME_HPP_INCLUDED

namespace lime {
   struct point {
      int x{};
      int y{};
   };

   struct color {
      unsigned char r{};
      unsigned char g{};
      unsigned char b{};
      unsigned char a{};
   };

   struct bitmap {
      int width{};
      int height{};
      color *data{};
   };

   namespace image {
      bool load(const char *filename, bitmap &image);
   } // !image

   namespace window {
      bool open(const int width, const int height, const char *title);
      void display(const bitmap &image);
      bool process();
   } // !window

   namespace mouse {
      enum class button {
         left,
         right,
         count,
      };

      point position();
      bool down(const button index);
      bool pressed(const button index);
      bool released(const button index);
   } // !mouse

   namespace keyboard {
      enum class key {
         back,
         tab,
         clear,
         enter,
         escape,
         space,
         page_up,
         page_down,
         end,
         home,
         left,
         up,
         right,
         down,
         insert,
         del,
         _0,
         _1,
         _2,
         _3,
         _4,
         _5,
         _6,
         _7,
         _8,
         _9,
         a,
         b,
         c,
         d,
         e,
         f,
         g,
         h,
         i,
         j,
         k,
         l,
         m,
         n,
         o,
         p,
         q,
         r,
         s,
         t,
         u,
         v,
         w,
         x,
         y,
         z,
         f1,
         f2,
         f3,
         f4,
         f5,
         f6,
         f7,
         f8,
         f9,
         f10,
         f11,
         f12,
         left_shift,
         right_shift,
         left_control,
         right_control,
         left_alt,
         right_alt,
         count,
      };

      bool down(const key index);
      bool pressed(const key index);
      bool released(const key index);
   } // !keyboard
} // !lime

#endif // !LIME_HPP_INCLUDED
