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

		// todo: construct frames for animation
		Bitmap frames[12];
		for( int i = 0; i < 12; i++ )
		{
			if( !bitmap::create(96, 96, frames[i]) )
			{
				return false;
			}

		}

		while( window::process() )
		{
			if( keyboard::pressed(keyboard::Key::Escape) )
			{
				break;
			}

			// todo: blit frame animation looping

			window::display(frames[0]);
		}
	}

	return 0;
}
