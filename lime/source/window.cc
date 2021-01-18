// window.cc

#include "lime.hpp"
#include "state.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>

namespace lime {
   namespace window {
      static struct {
         int width;
         int height;
         HWND window_handle;
         HDC device_context_handle;
         BITMAPINFO info;
         bitmap backbuffer;
      } state{};

      void init()
      {
      }
   } // !window

   static LRESULT main_window_proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
   {
      switch (uMsg) {
         case WM_CLOSE: PostQuitMessage(0); break;
         default: return DefWindowProcA(hWnd, uMsg, wParam, lParam);
      }
      
      return 0;
   }

   namespace window
   {
      bool open(const int width, const int height, const char *title)
      {
         state.width = width;
         state.height = height;

         WNDCLASSA wc = {};
         wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
         wc.lpfnWndProc = main_window_proc;
         wc.hInstance = GetModuleHandle(NULL);
         wc.hCursor = LoadCursor(NULL, IDC_ARROW);
         wc.hbrBackground = CreateSolidBrush(0x00000000);
         wc.lpszClassName = "limeWindowClassName";
         if (!RegisterClassA(&wc)) {
            return false;
         }

         // note: fix window actual size for style
         DWORD window_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
         RECT window_rect = { 0, 0, width, height };
         if (!AdjustWindowRect(&window_rect, window_style, FALSE)) {
            return false;
         }

         // note: center the window on screen
         int window_x = (GetSystemMetrics(SM_CXSCREEN) - window_rect.right) / 2;
         int window_y = (GetSystemMetrics(SM_CYSCREEN) - window_rect.bottom) / 2;

         // note: create the actual window
         state.window_handle = CreateWindowA(wc.lpszClassName,
                                           title,
                                           window_style,
                                           window_x,
                                           window_y,
                                           window_rect.right - window_rect.left,
                                           window_rect.bottom - window_rect.top,
                                           nullptr,
                                           nullptr,
                                           wc.hInstance,
                                           nullptr);
         if (state.window_handle == nullptr) {
            return false;
         }

         // note: device context handle and bitmap info header
         state.device_context_handle = GetDC(state.window_handle);
         state.info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         state.info.bmiHeader.biWidth = width;
         state.info.bmiHeader.biHeight = -height;
         state.info.bmiHeader.biPlanes = 1;
         state.info.bmiHeader.biBitCount = 32;
         state.info.bmiHeader.biCompression = BI_RGB;

         // note: debug backbuffer
         color *buf = (color *)VirtualAlloc(nullptr, sizeof(color) * (width / 2) * (height / 2), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
         state.backbuffer = { (width / 2), (height / 2), buf };
         for (int index = 0; index < (width / 2) * (height / 2); index++) {
            state.backbuffer.data[index] = {};
         }

         debug::init();

         // note: show window
         ShowWindow(state.window_handle, SW_SHOWNORMAL);

         return true;
      }

      bool process()
      {
         mouse::process();
         keyboard::process();

         MSG msg = {};
         while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
               return false;
            }

            TranslateMessage(&msg);
            DispatchMessageA(&msg);
         }

         return true;
      }

      void display(const bitmap &image)
      {
         const bitmap *src = &image;
         if (!src->data || src->width <= 0 || src->height <= 0) {
            src = &state.backbuffer;

            debug::state.counter++;
            const char *errmsg = "Trying to display an invalid bitmap!\n(data == nullptr, width <= 0, height <= 0)!";
            const int width    = debug::width(errmsg);
            const int center_x = (state.backbuffer.width - width) / 2;
            const int center_y = state.backbuffer.height / 2 - 4; 

            const int shift = (debug::state.counter >> 5) % 24;
            const unsigned counter = (0xffu << shift);
            const unsigned char r = (counter >>  0) & 0xff;
            const unsigned char g = (counter >>  8) & 0xff;
            const unsigned char b = (counter >> 16) & 0xff;
            const color c = { r, g, b, 255 };

            debug::log(state.backbuffer, center_x, center_y, c, errmsg);
         }

         state.info.bmiHeader.biWidth = src->width;
         state.info.bmiHeader.biHeight = -src->height;
         StretchDIBits(state.device_context_handle,
                       0,                  // dst x
                       0,                  // dst y
                       state.width,        // dst width
                       state.height,       // dst height
                       0,                  // src x
                       0,                  // src y
                       src->width,         // src width
                       src->height,        // src height
                       src->data,          // src data
                       &state.info,
                       DIB_RGB_COLORS,
                       SRCCOPY);
         Sleep(2);
      }
   } // !window
} // !lime
