#include "checkML.h"
#include "Game.h"
#include <fstream>
#include <filesystem>
#include <SDL.h>
#include <SDL_image.h>
#include "Laser.h"

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

Game::Game() : randomGenerator(time(nullptr)) {
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
	for (const auto i : textures)
		delete i;
	for (const auto i : sceneObjs)
		delete i; 
	delete infoBar;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{	
	//startMenu();
	infoBar = new InfoBar(Point2D<double>(0,WIN_HEIGHT - textures[spaceship]->getFrameHeight()), textures[spaceship], INFOBAR_PADDING, this);
	mothership = new Mothership(); // ...
	ufo = new Ufo(); // ...
	exampleInit(this); //ejemplo de 4x11
	startTime = SDL_GetTicks();
	while (!exit)
	{
		handleEvents();
		frameTime = SDL_GetTicks() - startTime;
		if (frameTime > TIME_BETWEEN_FRAMES) 
		{
			update();
			startTime = SDL_GetTicks();
		}
		render();
	}
	cout << "\n*** GAME OVER ***\n" << "*** PUNTUACION FINAL: " << playerPoints << " ***\n";
}

void Game::update()
{ // si los updates de cada elemento en cada vector dan falso se borra ese elemento y no se avanza el contador
	for (int i = 0; i < sceneObjs.size();)
		if (!sceneObjs[i]->update())
		{
			delete sceneObjs[i];
			sceneObjs.erase(sceneObjs.begin() + i);
		}
		else i++;

	if (alienUpdateTimer <= 0)
	{
		mothership->cannotMove();
		alienUpdateTimer = ALIEN_REFRESH_RATE;
	}
	else 
		alienUpdateTimer--;

	//if (aliens.empty() || cannons.empty())
		//exit = true;
}

void Game::render() const
{
	SDL_RenderClear(renderer);
	textures[stars]->render(); // el fondo!!!!!! :-)
	for (const auto i : sceneObjs) // los objetos
		i->render();
	infoBar->render();
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		if (event.type == SDL_QUIT) exit = true;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
		{
			saveGame("save");
			exit = true;
		}
		for (const auto i : cannons)
			i->handleEvent(event);
	}
}

void Game::startMenu() {
	cout << "CARGAR ARCHIVO DE GUARDADO? y/n\n";
	char read;
	cin >> read;
	while (read != 'y' && read != 'n')
	{
		cout << "Input a valid command (y/n)\n";
		cin >> read;
	}
	if (read == 'y')
		readSaveData("save", this);
	else
	{
		cout << "CARGAR MAPA? y/n\n";
		cin >> read;
		while (read != 'y' && read != 'n')
		{
			cout << "Input a valid command (y/n)\n";
			cin >> read;
		}
		if (read == 'y')
		{
			cout << "Nombre del mapa:\n";
			std::string mapName;
			cin >> mapName;
			readMap(mapName, this);
		}
		else
		{
			cout << "CARGANDO EJEMPLO\n";
			exampleInit(this);
		}
	}
}

void Game::exampleInit(Game *juego) {
	//Toda esta movida hace que el vector de aliens se llene con la cuadricula predeterminada de 4x11
	// aliens
	int type = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Point2D<double> position((textures[alien]->getFrameWidth() + 3) * j + 136, (textures[alien]->getFrameHeight() + 3) * i + 32); //+136 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			auto* pAlien = new Alien(position, type, textures[alien], this);
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
	auto* pCannon = new Cannon(posCan, textures[spaceship], this, 3);
	cannons.push_back(pCannon);
}

void Game::readMap(const std::string &mapName, Game *juego) {
	try {
		std::ifstream in(MAP_ROOT + mapName + ".txt");
		const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
		if (in.fail())
		{
			const std::error_code ec;
			const std::filesystem::path route = MAP_ROOT + mapName + ".txt";
			throw std::filesystem::filesystem_error("Could not read the specified file at " + route.string(), route, ec);
		}

		int read, x, y;
		while (cin >> read) {
			if (read == 0)
			{ // cannon
				cin >> x >> y;
				auto* pCannon = new Cannon(Point2D<double>(x, y), textures[spaceship], juego, 3);
				cannons.push_back(pCannon);
			}
			else if (read == 1)
			{ // alien
				int type;
				cin >> x >> y >> type;
				auto* pAlien = new Alien(Point2D<double>(x, y), type, textures[alien], juego);
				aliens.push_back(pAlien);
			}
			else if (read == 2)
			{ // bunker
				cin >> x >> y;
				auto* pBunker = new Bunker(Point2D<double>(x, y), 3, textures[bunker]);
				bunkers.push_back(pBunker);
			}
		}

		std::cin.rdbuf(cinbuf); //restablecer entrada
		in.close();
	} catch(std::filesystem::filesystem_error const& ex)
	{
		cerr << "Error while reading:\n" << ex.what() << endl;
		exampleInit(this); // se inicia un mapa genérico
	} catch(...)
	{
		cerr << "An error occurred during the scene load." << endl;
		exampleInit(this); // se inicia un mapa genérico
	}
}

void Game::saveGame(const std::string& saveFileName) {
	try {
		std::ofstream out(SAVE_FILE_ROOT + saveFileName + ".txt");

		if (out.fail())
		{
			const std::error_code ec;
			const std::filesystem::path route = SAVE_FILE_ROOT + saveFileName + ".txt";
			throw std::filesystem::filesystem_error("Could not read the specified file at " + route.string(), route, ec);
		}

		out << playerPoints << endl;

		for (int i = 0; i < cannons.size(); i++) {
			out << "0 " << (int)cannons[i]->getPos().getX() << " " << (int)cannons[i]->getPos().getY() << " " << cannons[i]->getLives() << endl;
		}
		for (int i = 0; i < aliens.size(); i++) {
			out << "1 " << (int)aliens[i]->getPos().getX() << " " << (int)aliens[i]->getPos().getY() << " " << aliens[i]->getType() << endl;
		}
		for (int i = 0; i < bunkers.size(); i++) {
			out << "2 " << (int)bunkers[i]->getPos().getX() << " " << (int)bunkers[i]->getPos().getY() << " " << bunkers[i]->getLives() << endl;
		}

		out.close();
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		cerr << "Error while saving:\n" << ex.what() << endl;
	}
	catch (...)
	{
		cerr << "An error occurred while saving." << endl;
	}
}

void Game::readSaveData(const std::string& saveFileName, Game* juego) {
	try {
		std::ifstream in(SAVE_FILE_ROOT + saveFileName + ".txt");
		const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
		if (in.fail())
		{
			const std::error_code ec;
			const std::filesystem::path route = SAVE_FILE_ROOT + saveFileName + ".txt";
			throw std::filesystem::filesystem_error("Could not read the specified file at " + route.string(), route, ec);
		}

		if (in.peek() == std::ifstream::traits_type::eof())
		{
			cout << "Empty save file, loading example\n";
			exampleInit(this);
		}
		cin >> playerPoints;

		int read, x, y;
		while (cin >> read) {
			if (read == 0)
			{ // cannon
				int lives;
				cin >> x >> y >> lives;
				auto* pCannon = new Cannon(Point2D<double>(x, y), textures[spaceship], juego, lives);
				cannons.push_back(pCannon);
			}
			else if (read == 1)
			{ // alien
				int type;
				cin >> x >> y >> type;
				auto* pAlien = new Alien(Point2D<double>(x, y), type, textures[alien], juego);
				aliens.push_back(pAlien);
			}
			else if (read == 2)
			{ // bunker
				int lives;
				cin >> x >> y >> lives;
				auto* pBunker = new Bunker(Point2D<double>(x, y), lives, textures[bunker]);
				bunkers.push_back(pBunker);
			}
		}

		std::cin.rdbuf(cinbuf); //restablecer entrada
		in.close();
	}
	catch (std::filesystem::filesystem_error const& ex)
	{
		cerr << "Error while reading:\n" << ex.what() << endl;
		exampleInit(this); // se inicia un mapa genérico
	}
	catch (...)
	{
		cerr << "An error occurred during the scene load." << endl;
		exampleInit(this); // se inicia un mapa genérico
	}
}

void Game::fireLaser(Point2D<double>&pos, Vector2D<>&speed, char friendly)
{
	auto* juego = this; // lvalue
	sceneObjs.push_back(new Laser(pos, speed, friendly, juego));
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<>(min, max)(randomGenerator);
}

bool Game::collisions(Laser* laser) const
{
	for (auto const i : sceneObjs)
	{
		if (SDL_HasIntersection(laser->getRect(), i->getRect()))
		{
			//...
			i->hit();
			return true;
		}
	}

	/// 
	if (laser->getColor() == FRIENDLY_CHAR)
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