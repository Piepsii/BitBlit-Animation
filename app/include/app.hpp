// app.hpp

#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <lime.hpp>

namespace lime
{
	namespace bitmap
	{
		bool valid(const Bitmap &image)
		{
			return image.data != nullptr;
		}

		bool create(const int width, const int height, Bitmap &image)
		{
			// todo: check if image has previously been allocated, 
			//       if so destroy it and do the below
			if( valid(image) )
			{
				destroy(image);
			}
			// todo: allocate the bitmap pixel data using 'width' and 'height'.
			int size = width * height;
			image.width = width;
			image.height = height;
			image.data = new Color[size];

			return valid(image);
		}

		bool inside(const Bitmap &image, const int x, const int y)
		{
			// todo: is the image valid?
			if( !valid(image) )
			{
				return false;
			}
			// todo: checks if 'x' and 'y' is inside the bitmap.
			int size = image.width * image.height;
			return y * image.width + x <= size && !(x < 0) && !(y < 0) ? true : false;
		}

		Color get(const Bitmap &image, const int x, const int y)
		{
			const Color magenta{ 255, 0, 255, 255 };
			// todo: is the image valid?
			if( !valid(image) )
			{
				return magenta;
			}
			// todo: is pixel inside the image?
			if( !inside(image, x, y) )
			{
				return magenta;
			}
			// todo: calculate the correct index for 'x' and 'y' in the 
			//       bitmap and return requested pixel color. 
			int index = y * image.width + x;
			return image.data[index];
		}

		void set(Bitmap &image, const int x, const int y, const Color &color)
		{
			// todo: is the image valid?
			if( !valid(image) )
			{
				return;
			}
			// todo: is pixel inside the image?
			if( !inside(image, x, y) )
			{
				return;
			}
			// todo: calculate the correct index for 'x' and 'y' in bitmap
			//       and set it to color 'c'
			int index = y * image.width + x;
			image.data[index] = color;
		}

		void clear(Bitmap &image, const Color &color)
		{
			if( !valid(image) )
			{
				return;
			}
			// todo: set all bitmap pixels to color 'c'
			for( int i = 0; i < image.width * image.height; i++ )
			{
				image.data[i] = color;
			}
		}

		void blit(const Bitmap &src, const Rectangle &rect, Bitmap &dst, const Point &pos)
		{
			// todo: blit a portion of 'src' specified by 'rect' onto the destination
			//       'dst' at the specified point 'pos'.
			if( !valid(src) ||
			   !valid(dst) ||
			   rect.height < 0 ||
			   rect.width < 0 ||
			   pos.x > dst.width ||
			   pos.x < 0 ||
			   pos.y > dst.height ||
			   pos.y < 0 )
			{
				return;
			}
			// todo: find rectangle in src
			int y_start = rect.y;
			int y_end = rect.y + rect.height;
			int x_start = rect.x;
			int x_end = rect.x + rect.width;
			int index, dstIndex;
			for( int y = y_start; y < y_end; y++ )
			{
				for( int x = x_start; x < x_end; x++ )
				{
					index = y * src.width + x;
					dstIndex = (pos.y + y - y_start) * dst.width + (pos.x + x - x_start);
					if( !(index > src.width * src.height || dstIndex > dst.height * dst.width) )
					{
						float alpha = static_cast<float>(src.data[index].a) / 255.f;
						dst.data[dstIndex].r = static_cast<unsigned char>(src.data[index].r * alpha) + static_cast<unsigned char>(dst.data[dstIndex].r * (1.f - alpha));
						dst.data[dstIndex].g = static_cast<unsigned char>(src.data[index].g * alpha) + static_cast<unsigned char>(dst.data[dstIndex].g * (1.f - alpha));
						dst.data[dstIndex].b = static_cast<unsigned char>(src.data[index].b * alpha) + static_cast<unsigned char>(dst.data[dstIndex].b * (1.f - alpha));

					}
				}
			}

			// todo: find pos in dst

			// todo: map rectangle onto dst
		}
	} // !image
} // !lime

#endif // !APP_HPP_INCLUDED
