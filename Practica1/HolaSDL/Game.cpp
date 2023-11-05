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
	//for (int i = 0; i < textures.size(); i++)
		//delete textures[i]; // IMPORTANTE: ESTE ES EL MEMORY LEAK pero no se porqué da error en el destructor de texture.cpp
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
	startTime = SDL_GetTicks();
	int i = 0;
	while (!exit)
	{
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime > FRAME_RATE) {
			update();
			startTime = SDL_GetTicks();
		}
		render();

	}

	cout << "\n*** GAME OVER ***\n";
}

void Game::update()
{ // si los updates de cada elemento en cada vector dan falso se borra ese elemento y no se avanza el contador
	for (int i = 0; i < lasers.size();)
		if (!lasers[i]->update())
		{
			delete lasers[i];
			lasers.erase(lasers.begin() + i);
		}
		else i++;
	if (alienUpdateTimer <= 0) {
		for (int i = 0; i < aliens.size();)
			if (!aliens[i]->update())
			{
				delete aliens[i];
				aliens.erase(aliens.begin() + i);
			}
			else i++;
		alienUpdateTimer = alienRefreshRate;
	}
	else
		alienUpdateTimer--;
	
	for (int i = 0; i < bunkers.size();)
		if (!bunkers[i]->update())
		{
			delete bunkers[i];
			bunkers.erase(bunkers.begin() + i);
		}
		else i++;
	for (int i = 0; i < cannons.size();)
		if (!cannons[i]->update())
		{
			delete cannons[i];
			cannons.erase(cannons.begin() + i);
		}
		else i++;

	if (aliens.empty() || cannons.empty())
		exit = true;
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	textures[stars]->render(); // el fondo!!!!!! :-)
	for (const auto i : aliens) // los objetos
		i->render();
	for (const auto i : bunkers)
		i->render();
	for (const auto i : cannons)
		i->render();
	for (const auto i : lasers)
		i->render(*renderer);
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

void Game::readMap(const std::string &mapName, Game *juego) {

	std::ifstream in(MAP_ROOT + mapName + ".txt");
	const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 

	int read, x, y;
	while (cin >> read) {
		if (read == 0) 
		{ // cannon
			cin >> x >> y;
			auto* pCannon = new Cannon(Point2D<double>(x,y), 3, textures[spaceship], juego);
			cannons.push_back(pCannon);
		}
		else if (read == 1) 
		{ // alien
			int type;
			cin >> x >> y >> type;
			auto* pAlien = new Alien(Point2D<double>(x,y), type, textures[alien], juego);
			aliens.push_back(pAlien);
		}
		else 
		{ // bunker
			cin >> x >> y;
			const Point2D<double> posBun(x, y);
			auto* pBunker = new Bunker(Point2D<double>(x,y), 3, textures[bunker]);
			bunkers.push_back(pBunker);
		}
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}

void Game::fireLaser(Point2D<double>&pos, Vector2D<>&speed, bool friendly)
{
	auto* juego = this;
	auto* laser = new Laser(pos, speed, friendly, juego);
	lasers.push_back(laser);
}

mt19937_64 randomGenerator(time(nullptr));
int Game::getRandomRange(const int& min, const int& max) {
	return uniform_int_distribution<>(min, max )(randomGenerator);
}

bool Game::collisions(Laser* laser) const
{ 
	if (laser->getFriendly())
	{ // si es del jugador choca contra los aliens, no contra los cañones
		for (const auto i : aliens)
			if (SDL_HasIntersection(laser->getRect(), i->getRect())) { i->hit(); return true; }
	}
	else
	{ // si es enemigo, no choca con el resto de aliens y sí con los cañones
		for (const auto i : cannons)
			if (SDL_HasIntersection(laser->getRect(), i->getRect())) { i->hit(); return true; }
	}

	// colisiones laser x laser
	for (const auto i : lasers)
			if (SDL_HasIntersection(laser->getRect(), i->getRect()) 
				&& laser->getFriendly() == !i->getFriendly() ) { i->hit(); return true; }

	// todos dañan los bunkeres
	for (const auto i : bunkers)
		if (SDL_HasIntersection(laser->getRect(), i->getRect())) { i->hit(); return true; }
	return false;
}



