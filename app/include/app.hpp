// app.hpp

#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <lime.hpp>

namespace lime {
   namespace bitmap {
      bool valid(const Bitmap &image)
      {
         return image.data != nullptr;
      }

      bool create(const int width, const int height, Bitmap &image)
      {
         // todo: check if image has previously been allocated, 
         //       if so destroy it and do the below
         // todo: allocate the bitmap pixel data using 'width' and 'height'.

         return valid(image);
      }

      bool inside(const Bitmap &image, const int x, const int y)
      {
         // todo: is the image valid?
         // todo: checks if 'x' and 'y' is inside the bitmap.

         return false;
      }

      Color get(const Bitmap &image, const int x, const int y)
      {
         const Color magenta{ 255, 0, 255, 255 };
         // todo: is the image valid?
         // todo: is pixel inside the image?
         // todo: calculate the correct index for 'x' and 'y' in the 
         //       bitmap and return requested pixel color. 

         return magenta;
      }

      void set(Bitmap &image, const int x, const int y, const Color &color)
      {
         // todo: is the image valid?
         // todo: is pixel inside the image?
         // todo: calculate the correct index for 'x' and 'y' in bitmap
         //       and set it to color 'c'
      }

      void clear(Bitmap &image, const Color &color)
      {
         if (!valid(image)) {
            return;
         }

         // todo: set all bitmap pixels to color 'c'
      }

      void blit(const Bitmap &src, const Rectangle &rect, Bitmap &dst, const Point &pos)
      {
         // todo: blit a portion of 'src' specified by 'rect' onto the destination
         //       'dst' at the specified point 'pos'.
         //
         //       make sure to validate 'rect' and determine correct portion of 
         //       the 'src' bitmap: 
         //        - x/y not negative
         //        - x/y is less than width and/or height of dst
         //        - width/height is not zero or negative
         //        - etc..
      }
   } // !image
} // !lime

#endif // !APP_HPP_INCLUDED
