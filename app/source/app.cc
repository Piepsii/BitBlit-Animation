// app.cc

#include "app.hpp"

int main(int argc, char **argv)
{
	using namespace lime; // note: window has to be 1280x720
	if( window::open(1280, 720, "lime") )
	{
		Bitmap tileset{};
		if( !bitmap::create("assets/explosion.bmp", tileset) )
		{
			return false;
		}

		Bitmap image{}; // note: has to be 320x180
		if( !bitmap::create(320, 180, image) )
		{
			return false;
		}



		while( window::process() )
		{
			if( keyboard::pressed(keyboard::Key::Escape) )
			{
				break;
			}

			// todo: blit frame animation looping
			for( int i = 0; i < 48; i++ )
			{
				Rectangle rect = { i / 4 * 96, 0, 96, 96 };
				Point pos = { 112, 42 };
				bitmap::blit(tileset, rect, image, pos);
				window::display(image);
				bitmap::clear(image, Color{ 0, 0, 0, 0 });
			}
		}
	}

	return 0;
}
