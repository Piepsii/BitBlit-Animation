// keyboard.cc

#include "lime.hpp"
#include "state.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace lime {
   namespace keyboard {
      void process()
      {
         for (auto &key : state.keys) {
            key.previous = key.current;
         }

         const int vkeys[] = 
         { 
            VK_BACK,
            VK_TAB,
            VK_CLEAR,
            VK_RETURN,
            VK_ESCAPE,
            VK_SPACE,
            VK_PRIOR,
            VK_NEXT,
            VK_END,
            VK_HOME,
            VK_LEFT,
            VK_UP,
            VK_RIGHT,
            VK_DOWN,
            VK_INSERT,
            VK_DELETE,
            '0',
            '1',
            '2',
            '3',
            '4',
            '5',
            '6',
            '7',
            '8',
            '9',
            'A',
            'B',
            'C',
            'D',
            'E',
            'F',
            'G',
            'H',
            'I',
            'J',
            'K',
            'L',
            'M',
            'N',
            'O',
            'P',
            'Q',
            'R',
            'S',
            'T',
            'U',
            'V',
            'W',
            'X',
            'Y',
            'Z',
            VK_F1,
            VK_F2,
            VK_F3,
            VK_F4,
            VK_F5,
            VK_F6,
            VK_F7,
            VK_F8,
            VK_F9,
            VK_F10,
            VK_F11,
            VK_F12,
            VK_LSHIFT,
            VK_RSHIFT,
            VK_LCONTROL,
            VK_RCONTROL,
            VK_LMENU,
            VK_RMENU,
         };

         int index = 0;
         for (auto &key : vkeys) {
            state.keys[index++].current = (GetAsyncKeyState(key) & 0x8000) != 0;
         }
      }

      bool down(const Key index)
      {
         return state.keys[int(index)].current;
      }

      bool pressed(const Key index)
      {
         return state.keys[int(index)].current && !state.keys[int(index)].previous;
      }

      bool released(const Key index)
      {
         return !state.keys[int(index)].current && state.keys[int(index)].previous;
      }
   } // !keyboard
} // !lime
