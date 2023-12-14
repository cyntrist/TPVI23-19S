#include "checkML.h"
#include "Game.h"
#include <filesystem>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Laser.h"
#include "MainMenuState.h"
#include "SDLError.h"

using namespace std;

/// estructura para las texturas
struct sprite { 
	std::string name;
	int rows;
	int cols;
};

/// array de estructuras con las texturas que queremos usar
const sprite sprites[NUM_TEXTURES] { 
	sprite {"stars", 1, 1},
	sprite {"spaceship", 1, 1},
	sprite {"bunker", 1, 4},
	sprite {"alien", 3, 2},
	sprite {"ufo", 1, 2}
};

/// constructora de Game, inicializa las texturas, SDL y renderer
Game::Game() { 
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw SDLError("Error loading SDL window or renderer. "s + SDL_GetError());
	for (int i = 0; i < NUM_TEXTURES; i++)
	textures[i] = new Texture(renderer, (TEXTURE_ROOT + sprites[i].name + ".png").c_str(), sprites[i].rows, sprites[i].cols);
	SDL_RenderClear(renderer);
	stateMachine = new GameStateMachine();
	stateMachine->replaceState(new MainMenuState());
}

/// destructora de Game, borra la memoria dinámica, el renderer y la ventana y cierra le juego
Game::~Game() {
	for (const auto i : textures)
		delete i;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
