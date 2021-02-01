// app.cc

#include "app.hpp"

int main(int argc, char **argv)
{
   using namespace lime; // note: window has to be 1280x720
   if (window::open(1280, 720, "lime")) {
      Bitmap tilemap{};
      if (!bitmap::create("assets/explosion.bmp", tilemap)) {
         return false;
      }

      Bitmap image{}; // note: has to be 320x180
      if (!bitmap::create(320, 180, image)) {
         return false;
      }

      // todo: create frames for animation

      while (window::process()) {
         if (keyboard::pressed(keyboard::Key::Escape)) {
            break;
         }

         // todo: blit frame animation looping

         window::display(image);
      }
   }

   return 0;
}
