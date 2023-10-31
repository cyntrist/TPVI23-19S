﻿#include "Game.h"
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
	sprite {"alien", 3, 2}
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
	SDL_RenderClear(renderer);
}

Game::~Game() {
	// sigue dando infraccion de acceso de lectura no se por que
	//auto newEnd = std::remove(textures.begin(), textures.end(), NUM_TEXTURES); // como es array fijo no se puedde borrar segun internet
	for (const auto i : aliens)
		delete i;
	for (const auto i : bunkers)
		delete i;
	for (const auto i : cannons)
		delete i;
	for (const auto i : lasers)
		delete i; 
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{	
	auto* juego = this;
	std::string mapName = "original";

	readMap(mapName, juego);

	//exampleInit(juego); //ejemplo de 4x11

	while (!exit)
	{
		handleEvents();
		update();
		render();
	}
}

void Game::update()
{
	for (const auto i : aliens)
		i->update();
	for (const auto i : bunkers)
		i->update();
	for (const auto i : cannons)
		i->update();
	for (const auto i : lasers)
		i->update();
}

void Game::render() const
{

	SDL_RenderClear(renderer);
	textures[stars]->render(); // el fondo!!!!!! :-)

	/*
	for (int i = 0; i < NUM_TEXTURES; i++) // debugging
		textures[i]->render();
	*/

	for (const auto i : aliens)
		i->render();
	for (const auto i : bunkers)
		i->render();
	for (const auto i : cannons)
		i->render();
	for (const auto i : lasers)
		i->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT) exit = true;
		for (const auto i : cannons)
				i->handleEvent(event);
	}
}

int Game::getDirection() {
	return movDir;
}

void Game::cannotMove() {
	movDir = -movDir;
}

void Game::exampleInit(Game *juego) {

	//Toda esta movida hace que el vector de aliens se llene con la cuadricula predeterminada de 4x11

	//ah y no tengo ni idea de si esto es necesario o no, no entiendo nada respecto a la arquitectura del juego la vd
	/// he quitado una de las variables intermedias (la de texture del alien) por probar!! si te parece bien 
	//tmb intente hacer los aliens sin todas estas variables intermedias pero no se por que no conseguia que funcionase, probe a almacenar las cosas en varibales y entonces ya funciono


	// aliens
	int type = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Point2D<double> position((textures[alien]->getFrameWidth() + 3) * j + 136, (textures[alien]->getFrameHeight() + 3) * i + 32); //+136 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			Alien* pAlien = new Alien(position, type, textures[alien], juego);
			aliens.push_back(pAlien);

			if (aliens.size() == 11 || aliens.size() == 22)
				type++;
		}
	}

	// cuatro unidad de bunker
	for (uint i = 1; i < 5; i++)
	{
		const Point2D<double> posBun(WIN_WIDTH * i / 5 - textures[bunker]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 4.0 - textures[bunker]->getFrameHeight());
		auto* pBunker = new Bunker(posBun, 3, textures[bunker]);
		bunkers.push_back(pBunker);
	}

	// a ver el cañon
	Point2D<double> posCan(WIN_WIDTH / 2 - textures[spaceship]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 8.0 - textures[spaceship]->getFrameHeight());
	auto* pCannon = new Cannon(posCan, 3, textures[spaceship], juego);
	cannons.push_back(pCannon);
}

void Game::readMap(std::string &mapName, Game *juego) {

	std::ifstream in(MAP_ROOT + mapName + ".txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 

	int read;
	while (cin >> read) {

		if (read == 0) {

			int x, y;
			cin >> x >> y;
			Point2D<double> posCan(x, y);
			auto* pCannon = new Cannon(posCan, 3, textures[spaceship], juego);
			cannons.push_back(pCannon);

		}
		else if (read == 1) {

			int x, y, type;
			cin >> x >> y >> type;
			Point2D<double> position(x, y);
			Alien* pAlien = new Alien(position, type, textures[alien], juego);
			aliens.push_back(pAlien);

		}
		else{

			int x, y;
			cin >> x >> y;
			const Point2D<double> posBun(x, y);
			auto* pBunker = new Bunker(posBun, 3, textures[bunker]);
			bunkers.push_back(pBunker);
		}
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}