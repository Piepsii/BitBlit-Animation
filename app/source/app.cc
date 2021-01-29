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

      // todo: 
      // 1. create a map using tiles from 'overworld.bmp'
      //    - map must be an island (20x12 tiles)
      //    - map must have forests
      //    - map must have varied grass tiles
      //    - map must have mountains
      //    - map must have two towns
      //    - can be hard coded 
      //    - can be generated 
      //    - can be read from file
      //    - island must be centered on screen
      //
      // 2. blit all tiles onto bm
      //    - foreach(tile : tiles) 
      //         image::blit(bm, tile.pos, ss, tile.rect)

      while (window::process()) {
         if (keyboard::pressed(keyboard::Key::Escape)) {
            break;
         }

         window::display(image);
      }
   }

   return 0;
}
