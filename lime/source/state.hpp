// state.hpp

#ifndef STATE_HPP_INCLUDED
#define STATE_HPP_INCLUDED

#include "lime.hpp"

namespace lime {
   namespace mouse {
      void process();

      struct {
         point position;
         struct {
            bool current;
            bool previous;
         } buttons[int(button::count)];
      } state{};
   } // !mouse

   namespace keyboard {
      void process();

      struct {
         struct {
            bool current;
            bool previous;
         } keys[int(key::count)];
      } state{};
   } // !keyboard

   namespace debug {
      void init();
      void log(bitmap &dst, int x, int y, color c, const char *format, ...);
      int  width(const char *text);

      struct {
         unsigned counter{};
         bitmap font{};
      } state{};
   } // !debug
} // !lime

#endif // !STATE_HPP_INCLUDED
