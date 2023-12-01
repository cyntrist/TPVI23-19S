#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SDL.h"
#include "Game.h"

#include "InvadersError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 


using uint = unsigned int;

int main(int argc, char* argv[])
{
	try
	{
		auto game = Game();
		game.run();
	}
	catch(FileFormatError& error)
    {
		std::cout << error.what() << std::endl;
	}
	catch(const std::string& ex)
	{
		std::cout << "ERROR: " << ex << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR: Exception not defined." << std::endl;
	}
	return 0;
}
