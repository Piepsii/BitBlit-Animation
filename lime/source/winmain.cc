// winmain.cc

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <windowsx.h>
#include <cstdlib>

extern int main(int argc, char **argv);

int WINAPI WinMain(HINSTANCE instace, HINSTANCE prev_instance, LPSTR command_line, int command_show)
{
   return main(__argc, __argv);
}
