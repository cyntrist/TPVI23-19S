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
	catch (...)
	{
		
	}
	return 0;
}
