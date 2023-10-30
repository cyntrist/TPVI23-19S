#include "checkML.h"

#include "Vector2D.h"
#include "texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	auto game = Game();

	game.run();
	game.~Game();
	return 0;
}
