#include "Game.h"
#include <SDL.h>

using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error loading SDL window or renderer"s;
	SDL_RenderClear(renderer);
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		SDL_RenderCopy(renderer, textures[i], textures[i]->);
	}
	SDL_RenderPresent(renderer);
}

Game::~Game() {
	for (uint i = 0; i < NUM_TEXTURES; i++) delete textures[i];
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit)
	{
		handleEvents();
		update();
		render();
	}
}

void Game::update()
{
	// ...
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	// ...
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT) exit = true;
		// ...
	}
}
