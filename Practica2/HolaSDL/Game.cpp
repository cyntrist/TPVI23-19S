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

const sprite sprites[NUM_TEXTURES] { 
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

/// GAME LOGIC BLOCK
void Game::run()
{	
	//startMenu();
	infoBar = new InfoBar(Point2D<>(0,WIN_HEIGHT - textures[spaceship]->getFrameHeight()), textures[spaceship], INFOBAR_PADDING, this);
	mothership = new Mothership(); // ...
	//exampleInit(); //ejemplo de 4x11
	readData("lluvia", this, true);
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
	for (const auto i : sceneObjs) 
		i->update(); //algo hace un acceso que no deberia
	for (const auto i : deleteObjs)
	{
		sceneObjs.erase(i->getIterator());
		delete i;
	}
	deleteObjs.clear();

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

/// INPUT BLOCK
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
		else if (cannon != nullptr) 
			cannon->handleEvent(event);
	}
}

/// INITIALIZATION BLOCK
void Game::startMenu() {
	cout << "CARGAR ARCHIVO DE GUARDADO? y/n\n";
	char read;
	cin >> read;
	//read = std::tolower(read);
	while (read != 'y' && read != 'n')
	{
		cout << "Input a valid command (y/n)\n";
		cin >> read;
	}
	if (read == 'y')
		readData("save", this, false);
	else
	{
		cout << "CARGAR MAPA? y/n\n";
		cin >> read;
		//read = std::tolower(read);
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
			readData(mapName, this, true);
		}
		else
		{
			cout << "CARGANDO EJEMPLO\n";
			exampleInit();
		}
	}
}

void Game::exampleInit() {
	auto it = sceneObjs.begin();
	Point2D<> position;
	SceneObject* object;
	// aliens
	int type = 0;
	for (int i = 0; i < 4; i++)
	{
		if (i == 1 || i == 3)
			type++;
		for (int j = 0; j < 11; j++)
		{
			position = Point2D<>((textures[alien]->getFrameWidth() + 3) * j + 136, (textures[alien]->getFrameHeight() + 3) * i + 32); //+136 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			if (type == 0) 
				object = new ShooterAlien(position, type, textures[alien],this, mothership);
			else 
				object = new Alien(position, type, textures[alien], this);

			addObject(object);
			mothership->addAlienCount();
		}
	}

	// bunkers
	for (uint i = 0; i < 4; i++)
	{
		position = Point2D<>(WIN_WIDTH * i / 5 - textures[bunker]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 4.0 - textures[bunker]->getFrameHeight());
		object = new Bunker(position, 4, textures[bunker], this);
		addObject(object);
	}

	// cannon
	position = Point2D<>(WIN_WIDTH / 2 - textures[spaceship]->getFrameWidth() / 2, WIN_HEIGHT - WIN_HEIGHT / 8.0 - textures[spaceship]->getFrameHeight());
	auto* newCannon = new Cannon(position, textures[spaceship], this, 3);
	sceneObjs.push_back(newCannon);
	it = --sceneObjs.end();
	newCannon->setIterator(it);
	newCannon->updateRect();
	//object = static_cast<SceneObject*>(newCannon); // para probar el static casting porque estoy SUPER SUPER ultra mega segura de que puedo hacerlo
	//addObject(object);
	cannon = newCannon;

	// el ufo (IMPORTANTE: puede haber varios)
	position = Point2D<>(WIN_WIDTH, WIN_HEIGHT / 2); 
	object = new Ufo(position, textures[ufos], this, false, visible);
	addObject(object);
}

void Game::addObject(SceneObject*& object)
{ // método para simplificar las inicializaciones del tablero 
	sceneObjs.push_back(object);
	const auto it = --sceneObjs.end();
	object->setIterator(it);
	object->updateRect();
}

/// DATA MANAGEMENT BLOCK
void Game::saveData(const std::string& saveFileName) const {
	std::ofstream out(SAVE_FILE_ROOT + saveFileName + ".txt");
	if (out.fail())
		throw "Could not find the specified save file"s;
	for (const auto i : sceneObjs)
		i->save(out);
	out.close();
}

void Game::readData(const std::string& filename, Game* juego, bool isMap) {
	string fileroot;
	if (!isMap) fileroot = SAVE_FILE_ROOT + filename + ".txt";
	else fileroot = MAP_ROOT + filename + ".txt";
	std::ifstream in(fileroot);
	const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
	if (in.fail())
		throw "Could not read the specified data file at "s + fileroot ;
	if (in.peek() == std::ifstream::traits_type::eof())
		throw "Empty save file, loading example\n"s;

	auto it = sceneObjs.begin();
	int read, x, y, lives, timer, type, state, level;
	int alienCount = 0;
	char color;
	SceneObject* object = nullptr; // para simplificar
	while (cin >> read) {
		cin >> x >> y;
		auto position  = Point2D<>(x, y);
		switch (read)
		{
		case 0: // cannon
		{
			cin >> lives >> timer;
			auto* newCannon = new Cannon(position, textures[spaceship], juego, lives, timer);
			cannon = newCannon;
			object = static_cast<SceneObject*>(newCannon); // porque estoy super super segura de esto (casting ascendente) y asi puedo simplificar con el método addObject y una sola variable sceneobject para toda esta parafernalia
			break;
		}
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
			//mothership = new Mothership(-1, alienCount, state, level, this, timer); // NO PARA DE DARME ERRORES MOTHERSHIP QUE ESTÁ PRACTICAMENTE VACIA NO SE QUE LE PASA!!!
			break;
		case 4: // bunker
			cin >> lives;
			object = new Bunker(position, lives, textures[bunker], this);
			break;
		case 5: // ufo
			cin >> y >> state >> timer;
			object = new Ufo(position, textures[ufos], this, false, state, timer);
			break;
		case 6: // laser
		{
			cin >> color;
			auto speed = Vector2D<>(0, -LASER_MOV_SPEED);
			object = new Laser(position, speed, color, this);
			break;
		}
		case 7: // score
			playerPoints = x;
			break;
		default: // nada
			break;
		}
		if (object != nullptr)
			addObject(object);
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}

/// GAME COLLISIONS BLOCK
void Game::fireLaser(Point2D<>&pos, Vector2D<>&speed, const char friendly)
{ 
	SceneObject* pLaser = new Laser(pos, speed, friendly, this);
	addObject(pLaser);
}

bool Game::collisions(Laser* laser) const
{
	for (auto const i : sceneObjs)
		if (i->hit(laser->getRect(), laser->getColor()))
			return true;
	return false;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<>(min, max)(randomGenerator);
}