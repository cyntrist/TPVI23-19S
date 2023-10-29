#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

struct sprite {
	const std::string name;
	int rows;
	int cols;
};

const sprite sprites[NUM_TEXTURES]{ 
	sprite {"stars", 1, 1},
	sprite {"spaceship", 1, 1},
	sprite {"bunker", 1, 4},
	sprite {"aliens", 3, 2}
};

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw "Error loading SDL window or renderer"s;
	for (int i = 0; i < NUM_TEXTURES; i++)
		textures[i] = new Texture(renderer, (TEXTURE_ROOT + sprites[i].name + ".png").c_str(), sprites[i].rows, sprites[i].cols);
	// pruebita
	Alien alien = Alien();
	Bunker bunker = Bunker();
	Cannon cannon = Cannon();
	SDL_RenderClear(renderer);
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
	for (int i = 0; i < NUM_TEXTURES; i++) // debugging
		textures[i]->render();
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

int Game::getDirection() {
	return movDir;
}

void Game::cannotMove() {
	movDir = -movDir;
}