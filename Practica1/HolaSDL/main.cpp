#include "checkML.h"
#include "Vector2D.h"
#include "texture.h"
#include "SDL.h"
#include "Game.h"

using uint = unsigned int;

int main(int argc, char* argv[])
{
	auto game = Game();
	game.run();
	return 0;
}
