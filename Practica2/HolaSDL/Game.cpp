#include "checkML.h"
#include "Game.h"
#include <fstream>
#include <filesystem>
#include <SDL.h>
#include <SDL_image.h>
#include "Laser.h"
#include "Alien.h"
#include "Bunker.h"
#include "ShooterAlien.h"
#include "Mothership.h"
#include "Ufo.h"

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
	sprite {"alien", 3, 2},
	sprite {"ufo", 1, 2}
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
	delete mothership;
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
	exampleInit(); //ejemplo de 4x11
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
	for (auto it = sceneObjs.begin(); it != sceneObjs.end();) {
        if (!(*it)->update())
        {
			delete *it;
        	it = sceneObjs.erase(it);
        }
        else 
			++it;
    }

	/// VERSION ANTIGUA:
	// No está toodo de la version antigua porque lo he movido ya sea a alien o a mothership y soy idiota perdon
	/*		
	if (alienUpdateTimer <= 0)
	{
		mothership->cannotMove();
		alienUpdateTimer = ALIEN_REFRESH_RATE;
	}
	else 
		alienUpdateTimer--;
	

	if (aliens.empty() || cannons.empty())
		exit = true;
	*/
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
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_g)
		{
			saveData("save");
			endGame();
		}
		else
		{
			for (const auto i : sceneObjs)
			{ // funciona directamente poniendo i->handleEvent()... pero por qué? lo unico que entiendo es que es mejor hacer este casting pero no se...
				auto* cannon = dynamic_cast<Cannon*>(i);
				if (cannon != nullptr) 
					cannon->handleEvent(event);
			}
			/*for (const auto i : sceneObjs) {
				i->handleEvent(event);
			}*/
		}
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
		readData("save", this);
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
			exampleInit();
		}
	}
}

void Game::exampleInit() {
	// aliens
	auto it = sceneObjs.begin();
	int type = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 1 || i == 3)
			type++;
		for (int j = 0; j < 11; j++)
		{
			Point2D<double> position((textures[alien]->getFrameWidth() + 3) * j + 136, (textures[alien]->getFrameHeight() + 3) * i + 32); //+136 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			if (type == 0) {
				//los shooter aliens hacen que el juego pete en el update, es por el fire laser del game
				auto* pShAlien = new ShooterAlien(position, type, textures[alien],this, mothership);
				sceneObjs.push_back(pShAlien);
				pShAlien->updateRect();
				if (it != sceneObjs.end())
					pShAlien->setIterator(++it);
				mothership->addAlienCount();
			}
			else {
				auto* pAlien = new Alien(position, type, textures[alien], this);
				sceneObjs.push_back(pAlien);
				pAlien->updateRect();
				if (it != sceneObjs.end())
					pAlien->setIterator(++it);
				mothership->addAlienCount();
			}
		}
	}


	// bunkers
	for (uint i = 1; i < 5; i++)
	{
		const Point2D<double> posBun(WIN_WIDTH * i / 5 - textures[bunker]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 4.0 - textures[bunker]->getFrameHeight());
		auto* pBunker = new Bunker(posBun, 3, textures[bunker], this);
		sceneObjs.push_back(pBunker);
		if (it != sceneObjs.end())
			pBunker->setIterator(++it);
	}

	// cannon
	const Point2D<double> posCan(WIN_WIDTH / 2 - textures[spaceship]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 8.0 - textures[spaceship]->getFrameHeight());
	auto* pCannon = new Cannon(posCan, textures[spaceship], this, 3);
	sceneObjs.push_back(pCannon);
	pCannon->updateRect();
	if (it != sceneObjs.end())
		pCannon->setIterator(++it);

	// el ufo (IMPORTANTE: puede haber varios)
	const Point2D<double> posUfo(WIN_WIDTH, WIN_HEIGHT / 2); 
	auto* pUfo = new Ufo(posUfo, textures[ufos], this, false, visible);
	sceneObjs.push_back(pUfo);
	pUfo->updateRect();
	if (it != sceneObjs.end())
		pUfo->setIterator(++it);
}

void Game::readMap(const std::string &mapName, Game *juego) {

	/// VERSION ANTIGUA:
	/*
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
	*/
}

void Game::saveData(const std::string& saveFileName) {

	/// VERSION ANTIGUA:
	/*
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
	*/
}

void Game::readData(const std::string& filename, Game* juego, bool isMap) {
	string fileroot;
	if (isMap) fileroot = SAVE_FILE_ROOT + filename + ".txt";
	else fileroot = MAP_ROOT + filename + ".txt";
	std::ifstream in(fileroot);
	const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
	if (in.fail())
	{
		exampleInit(); // esto debería moverse en el futuro al catch de ambos 
		throw "Could not read the specified file"s;
	}
	if (in.peek() == std::ifstream::traits_type::eof())
	{
		exampleInit(); // esto debería moverse en el futuro al catch de ambos 
		throw "Empty save file, loading example\n"s;
	}

	auto it = sceneObjs.begin();
	int read, x, y, lives, timer, type, state, level;
	int alienCount = 0;
	char color;
	SceneObject* object = nullptr; // para simplificar, espero saber usarlo
	while (cin >> read) {
		cin >> x >> y;
		auto position  = Point2D<double>(x, y);
		switch (read)
		{
		case 0: // cannon
			cin >> lives >> timer;
			object = new Cannon(position, textures[spaceship], juego, lives, timer);
			break;
		case 1: // alien
			cin >> type;
			object = new Alien(position, type, textures[alien], this, mothership);
			alienCount++;
			break;
		case 2: // shooter alien
			cin >> type >> timer;
			object = new ShooterAlien(position, type, textures[alien], this, mothership);
			alienCount++;
			break;
		case 3: // mothership
			cin>> state >> level >> timer;
			mothership = new Mothership(-1, alienCount, state, level, this, timer); // *********
			break;
		case 4: // bunker
			cin >> y >> lives;
			object = new Bunker(position, lives, textures[bunker], this);
			break;
		case 5: // ufo
			cin >> y >> state >> timer;
			object = new Ufo(position, textures[ufos], this, false, state, timer);
			break;
		case 6: // laser
			cin >> color;
			auto speed = Vector2D<>(0, -LASER_MOV_SPEED);
			object = new Laser(position, speed, color, this);
			break;
		case 7: // score
			playerPoints = x;
			break;
		default: // nada
			throw "Invalid type of object"s;
		}
	}
	if (object != nullptr)
	{
		sceneObjs.push_back(object);
		object->updateRect();
			if (it != sceneObjs.end())
				object->setIterator(++it);
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}

void Game::fireLaser(Point2D<double>&pos, Vector2D<>&speed, char friendly)
{ //Esto peta
	auto* pLaser = new Laser(pos, speed, friendly, this);
	sceneObjs.push_back(pLaser);
	const auto it = --sceneObjs.end();
	pLaser->setIterator(it);
	pLaser->updateRect();
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<>(min, max)(randomGenerator);
}

bool Game::collisions(Laser* laser) const
{
	for (auto const i : sceneObjs)
		if (i->hit(laser->getRect(), laser->getColor()))
			return true;
	return false;
}