// state.hpp

#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "lime.hpp"

namespace lime {
   namespace mouse {
      void process();

      struct {
         Point position;
         struct {
            bool current;
            bool previous;
         } buttons[int(Button::Count)];
      } state{};
   } // !mouse

   namespace keyboard {
      void process();

      struct {
         struct {
            bool current;
            bool previous;
         } keys[int(Key::Count)];
      } state{};
   } // !keyboard

   namespace debug {
      void init();
      void log(Bitmap &dst, int x, int y, Color c, const char *format, ...);
      int  width(const char *text);

      struct {
         unsigned counter{};
         Bitmap font{};
      } state{};
   } // !debug
} // !lime

#endif // !STATE_HPP_INCLUDED
