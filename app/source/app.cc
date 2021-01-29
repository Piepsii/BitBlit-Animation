// app.cc

#include "app.hpp"

int main(int argc, char **argv)
{
   using namespace lime;
   if (window::open(1280, 720, "lime")) {
      Bitmap tilemap{};
      if (!bitmap::create("assets/overworld.bmp", tilemap)) {
         return false;
      }

      Bitmap image{};
      if (!bitmap::create(640, 360, image)) {
         return false;
      }

      // todo: create or generate world map

      while (window::process()) {
         if (keyboard::pressed(keyboard::Key::Escape)) {
            break;
         }

         // todo: blit all tiles

         window::display(image);
      }
   }

   return 0;
}
