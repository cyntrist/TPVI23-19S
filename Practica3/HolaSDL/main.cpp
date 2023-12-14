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
	}
	catch(FileNotFoundError& fileError)
    {
		std::cout << fileError.what() << std::endl;
	}
	catch(SDLError& SDLError)
	{
		std::cout << SDLError.what() << std::endl;
	}
	catch (FileFormatError& fileError)
	{
		std::cout << fileError.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR: Exception not defined." << std::endl;
	}
	return 0;
}
