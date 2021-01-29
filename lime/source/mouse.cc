// mouse.cc

#include "lime.hpp"
#include "state.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace lime {
   namespace mouse {
      void process()
      {
         for (auto &button : state.buttons) {
            button.previous = button.current;
         }

         POINT p{};
         GetCursorPos(&p);
         ScreenToClient(GetActiveWindow(), &p);
         state.position = { p.x, p.y };

         const int vkeys[] = 
         { 
            VK_LBUTTON, 
            VK_RBUTTON 
         };

         int index = 0;
         for (auto &key : vkeys) {
            state.buttons[index++].current = (GetAsyncKeyState(key) & 0x8000) != 0;
         }
      }

      Point position()
      {
         return state.position;
      }
    
      bool down(const Button index)
      {
         return state.buttons[int(index)].current;
      }

      bool pressed(const Button index)
      {
         return state.buttons[int(index)].current && !state.buttons[int(index)].previous;
      }

      bool released(const Button index)
      {
         return !state.buttons[int(index)].current && state.buttons[int(index)].previous;
      }
   } // !mouse
} // !lime
