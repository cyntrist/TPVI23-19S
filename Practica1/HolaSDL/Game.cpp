#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error loading SDL window or renderer"s;
	SDL_RenderClear(renderer);

	// todo esto hay que reformarlo, solo estoy probando
	Texture* fondo = new Texture(renderer, "..\\images\\stars.png", 1, 1); // esto debería ser parte de texturas
	fondo->render();

	SDL_RenderPresent(renderer);
	SDL_Delay(5000);
	delete fondo;
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
	for (int i = 0; i < aliens.size(); i++)
		aliens[i]->render();
	for (int i = 0; i < bunkers.size(); i++)
		bunkers[i]->render();
	for (int i = 0; i < cannons.size(); i++)
		cannons[i]->render();
	for (int i = 0; i < lasers.size(); i++)
		lasers[i]->render();
	SDL_RenderPresent(renderer);
	//std::any_cast<decltype(i)>(elements[i])(render);
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
