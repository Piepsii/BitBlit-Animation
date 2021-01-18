// app.hpp

#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <lime.hpp>

namespace lime {
   namespace image {
      inline bool valid(const bitmap &bm)
      {
         return bm.data != nullptr;
      }
   } // !image
} // !lime

#endif // !APP_HPP_INCLUDED
