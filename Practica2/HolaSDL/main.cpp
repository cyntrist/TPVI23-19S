#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SDL.h"
#include "Game.h"

using uint = unsigned int;

int main(int argc, char* argv[])
{
	try
	{
		auto game = Game();
		game.run();
	}
	catch(const std::string& ex)
	{
		// 		exampleInit(); 
		std::cout << "ERROR: " << ex << std::endl;
	}
	catch (...)
	{
		std::cout << "ERROR: Excepcion no definida." << std::endl;
	}
	return 0;
}
