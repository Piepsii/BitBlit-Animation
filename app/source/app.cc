// app.cc

#include "app.hpp"

int main(int argc, char **argv)
{
   using namespace lime;
   
   bitmap ss;
   if (!image::create("assets/overworld.bmp", ss)) {
      return false;
   }

   if (window::open(1280, 720, "lime")) {
      bitmap bm{};

      while (window::process()) {
         if (keyboard::pressed(keyboard::key::escape)) {
            break;
         }

         window::display(ss);
      }
   }

   return 0;
}
