﻿#include "checkML.h"
#include "Game.h"
#include <fstream>
#include <filesystem>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Laser.h"
#include "Alien.h"
#include "Bunker.h"
#include "ShooterAlien.h"
#include "Mothership.h"
#include "Ufo.h"

#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 

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
Game::Game() : randomGenerator(time(nullptr)) { 
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
}

/// destructora de Game, borra la memoria dinámica, el renderer y la ventana y cierra le juego
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

/// GAME LOGIC BLOCK:
/// muestra el menú inicial e inicializa los GameObjects y el tablero acorde a él, después va el bucle principal del juego
/// con llamadas a los métodos principales, gestiona el framerate y tras acabar el bucle ppal la puntuación por consola*/
void Game::run()
{ 
	//startMenu();
	infoBar = new InfoBar(Point2D<>(0,WIN_HEIGHT - textures[spaceship]->getFrameHeight()), textures[spaceship], INFOBAR_PADDING, this, renderer);
	mothership = new Mothership(1, 0, 0, 0, this, 0);
	//exampleInit(); //ejemplo de 4x11
	emptyLists();
    readData("map" + std::to_string(mapLevel), this, true);
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
		if (mothership->getAlienCount() <= 0)
		{
			emptyLists();
			mothership->resetLevel();
			mapLevel = mapLevel % LEVEL_NUMBER;
			readData("map" + std::to_string(++mapLevel), this, true);
		}
	}
	cout << "\n*** GAME OVER ***\n" << "*** PUNTUACION FINAL: " << playerPoints << " ***\n";
}

/// recorre los objetos de escena y si alguno ha avisado de que ha muerto, estará en la lista de objetos a borrar
///	estos seran borrados y su memoria liberada, y la lista de objetos a borrar se limpiara
void Game::update()
{
	mothership->update();
	for (const auto i : sceneObjs) 
		i->update(); 
	for (const auto i : deleteObjs)
	{
		sceneObjs.erase(i->getIterator());
		delete i;
	}
	infoBar->update();
	deleteObjs.clear();
}

/// le aplica al renderer el fondo, la textura de cada objeto de escena y el infobar, y lo presenta en pantalla
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
///	gestiona los diferentes inputs que puede haber:
///	de Cannon (en su propio método, mov lateral y disparar),
///	de guardado (S),
///	de carga (L),
///	de mapa (M)
///	y de salida 
void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit)
	{
		SDL_Keycode key = event.key.keysym.sym;
		if (event.type == SDL_QUIT) exit = true;
		else if (event.type == SDL_KEYDOWN && (key == SDLK_s || key == SDLK_l ||key == SDLK_m))
		{
			if (key == SDLK_s) // guardar
			{
				std::cout << "Input save slot to save to: " << std::endl;
				char k;
				std::cin >> k;
				if (isdigit(k))
				{
					saveData("save" + std::to_string(k - '0'));
					endGame();
					std::cout << "Saved game." << std::endl;
				}
				else std::cout << "Invalid number, resuming game." << std::endl;
			}
			else if (key == SDLK_l)
			{
				std::cout << "Input save slot to load: " << std::endl;
				char k;
				std::cin >> k;
				if (isdigit(k))
				{
					emptyLists();
					readData("save" + std::to_string(k - '0'), this, false);
					std::cout << "Loaded game." << std::endl;
				}
				else std::cout << "Invalid number, resuming game." << std::endl;
			}
			else if (key == SDLK_m)
			{
				cout << "Map name: ";
				std::string mapName;
				cin >> mapName;
				emptyLists();
				readData(mapName, this, true);
			}
		}
		else if (cannon != nullptr) 
				cannon->handleEvent(event);
	}
}

/// INITIALIZATION BLOCK:
///	Muestra por consola diferentes mensajes para cargar o no un archivo guardado, un mapa o el tablero ejemplo
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
		readData("save", this, false);
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
			readData(mapName, this, true);
		}
		else
		{
			cout << "CARGANDO EJEMPLO\n";
			exampleInit();
		}
	}
}

/// genera un tablero ejemplo predeterminado (utilizado principalmente para debugging inicial)
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
			position = Point2D<>((textures[alien]->getFrameWidth() + 3) * j + 130,
			                     (textures[alien]->getFrameHeight() + 3) * i + 32);
			//+130 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			if (type == 0) 
				object = new ShooterAlien(position, type, textures[alien],this, mothership);
			else 
				object = new Alien(position, type, textures[alien], this, mothership);

			addObject(object);
			mothership->addAlienCount();
		}
	}

	// bunkers
	for (uint i = 1; i < 5; i++)
	{
		position = Point2D<>(WIN_WIDTH * i / 5 - textures[bunker]->getFrameWidth() / 2,
		                     WIN_HEIGHT - WIN_HEIGHT / 4.0 - textures[bunker]->getFrameHeight());
		object = new Bunker(position, 4, textures[bunker], this);
		addObject(object);
	}

	// cannon
	position = Point2D<>(WIN_WIDTH / 2 - textures[spaceship]->getFrameWidth() / 2,
	                     WIN_HEIGHT - WIN_HEIGHT / 8.0 - textures[spaceship]->getFrameHeight());
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

/// método para simplificar la generacion de objetos y los métodos en los que se generan las entidades de los tableros
///	puesto que se llama muchas veces a estas líneas de manera conjunta,
///	realiza el push back, la asignacion del iterador al objeto y actualiza su rectángulo inicialmente
void Game::addObject(SceneObject*& object)
{ // método para simplificar las inicializaciones del tablero 
	sceneObjs.push_back(object);
	const auto it = --sceneObjs.end();
	object->setIterator(it);
	object->updateRect();
}

/// metodo para vaciar ambas listas de objetos y liberar su memoria, usado previo a cargar partida o mapa
void Game::emptyLists()
{
	for (const auto i : sceneObjs)
		delete i;
	sceneObjs.clear();
	for (const auto i : deleteObjs)
		delete i;
	deleteObjs.clear();
}

/// DATA MANAGEMENT BLOCK:
///	invoca el método save() de cada objeto y guarda en el stream que se le proporciona sus datos
void Game::saveData(const std::string& saveFileName) const {
	std::ofstream out(SAVE_FILE_ROOT + saveFileName + ".txt");
	if (out.fail())
		throw FileNotFoundError("Could not read the save file called "s + saveFileName);
	for (const auto i : sceneObjs)
		i->save(out);
	out << "7 " << playerPoints << endl;
	out.close();
}

/// lee y añade al juego las diferentes entidades del archivo proporcionado, ya sea mapa o partida guardada
///	para gestionar esto último se utiliza un bool que indica si es mapa o no, para determinar la raíz de directorio
///	que le corresponde
void Game::readData(const std::string& filename, Game* juego, bool isMap) {
	string fileroot;
	if (!isMap) fileroot = SAVE_FILE_ROOT + filename + ".txt";
	else fileroot = MAP_ROOT + filename + ".txt";
	std::ifstream in(fileroot);
	const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
	if (in.fail())
		throw FileNotFoundError("Could not read the specified data file at "s + fileroot) ;
	if (in.peek() == std::ifstream::traits_type::eof())
		throw FileFormatError("Empty data file: "s + fileroot);

	auto it = sceneObjs.begin();
	int read, x, y, lives, timer, type, state, level;
	int alienCount = 0;
	char color;
	Point2D<> position;
	SceneObject* object; // para simplificar
	while (cin >> read) {
		object = nullptr;
		switch (read)
		{
		case 0: // cannon
		{
			cin >> x >> y;
			cin >> lives >> timer;
			position  = Point2D<>(x, y);
			cannon = new Cannon(position, textures[spaceship], juego, lives, timer);
			object = cannon;
			break;
		}
		case 1: // alien
			cin >> x >> y;
			cin >> type;
			position = Point2D<>(x, y);
			object = new Alien(position, type, textures[alien], this, mothership);
			mothership->addAlienCount();
			alienCount++;
			break;
		case 2: // shooter alien
			cin >> x >> y;
			cin >> type >> timer;
			position = Point2D<>(x, y);
			object = new ShooterAlien(position, type, textures[alien], this, mothership, timer);
			mothership->addAlienCount();
			alienCount++;
			break;
		case 3: // mothership
			cin >> x >> y; // para gastarlos
			cin >> state >> level >> timer;
			delete mothership;
			mothership = new Mothership(1, alienCount, state, level, this, timer);
			break;
		case 4: // bunker
			cin >> x >> y;
			cin >> lives;
			position = Point2D<>(x, y);
			object = new Bunker(position, lives, textures[bunker], this);
			break;
		case 5: // ufo
			cin >> x >> y;
			cin >> y >> state >> timer;
			position = Point2D<>(x, y);
			object = new Ufo(position, textures[ufos], this, false, state, timer);
			break;
		case 6: // laser
		{
			cin >> x >> y;
			cin >> color;
			position = Point2D<>(x, y);
			int direction = 1;
			if (color == 'r')
				direction = -1;
			auto speed = Vector2D(0, direction * LASER_MOV_SPEED);
			object = new Laser(position, speed, color, this);
			break;
		}
		case 7: // score
			cin >> playerPoints;
			break;
		default: // nada
			break;
		}
		if (object != nullptr)
			addObject(object);
	}

	/// manera feilla de actualizar la referencia a mothership de los aliens leidos
	for (const auto i : sceneObjs)
	{
		auto* alien = dynamic_cast<Alien*>(i); // si es shoo
		if (alien != nullptr)
			alien->setMothership(mothership);
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}

/// GAME COLLISIONS BLOCK:
///	genera un laser en la posicion, velocidad y color dados y lo añade a la escena
void Game::fireLaser(Point2D<>&pos, Vector2D<int>&speed, const char friendly)
{ 
	SceneObject* pLaser = new Laser(pos, speed, friendly, this);
	addObject(pLaser);
}

/// gestiona las colisiones entre el laser dado y cada objeto en la escena
///	devuelve true si ha colisionado con algo y se invocarán a los métodos
/// correspondientes
bool Game::damage(Laser* laser) const
{
	for (auto const i : sceneObjs)
		if (i->hit(laser->getRect(), laser->getColor()))
			return true;
	return false;
}

/// devuelve un número aleatorio entre min y max
int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<>(min, max)(randomGenerator);
}