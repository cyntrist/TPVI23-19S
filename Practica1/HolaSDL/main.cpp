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
	/*_crtBreakAlloc = 224;
	_crtBreakAlloc = 228;
	_crtBreakAlloc = 232;
	_crtBreakAlloc = 236;*/
	auto game = Game();
	game.run();
	game.~Game();
	return 0;
}
