// lime.hpp

#ifndef LIME_HPP_INCLUDED
#define LIME_HPP_INCLUDED

namespace lime {
   struct Point {
      int x{};
      int y{};
   };

   struct Rectangle {
      int x{};
      int y{};
      int width{};
      int height{};
   };

   struct Color {
      unsigned char b{};
      unsigned char g{};
      unsigned char r{};
      unsigned char a{};
   };

   struct Bitmap {
      int width{};
      int height{};
      Color *data{};
   };

   namespace bitmap {
      bool create(const char *filename, Bitmap &image);
      void destroy(Bitmap &image);
   } // !image

   namespace window {
      bool open(const int width, const int height, const char *title);
      void display(const Bitmap &image);
      bool process();
   } // !window

   namespace mouse {
      enum class Button {
         Left,
         Right,
         Count,
      };

      Point position();
      bool down(const Button index);
      bool pressed(const Button index);
      bool released(const Button index);
   } // !mouse

   namespace keyboard {
      enum class Key{
          Back,
          Tab,
          Clear,
          Enter,
          Escape,
          Space,
          PageUp,
          PageDown,
          End,
          Home,
          Left,
          Up,
          Right,
          Down,
          Insert,
          Del,
          Num0,
          Num1,
          Num2,
          Num3,
          Num4,
          Num5,
          Num6,
          Num7,
          Num8,
          Num9,
          A,
          B,
          C,
          D,
          E,
          F,
          G,
          H,
          I,
          J,
          K,
          L,
          M,
          N,
          O,
          P,
          Q,
          R,
          S,
          T,
          U,
          V,
          W,
          X,
          Y,
          Z,
          F1,
          F2,
          F3,
          F4,
          F5,
          F6,
          F7,
          F8,
          F9,
          F10,
          F11,
          F12,
          LeftShift,
          RightShift,
          LeftControl,
          RightControl,
          LeftAlt,
          RightAlt,
          Count,
      };

      bool down(const Key index);
      bool pressed(const Key index);
      bool released(const Key index);
   } // !keyboard
} // !lime

#endif // !LIME_HPP_INCLUDED
