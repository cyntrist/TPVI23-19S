#include "checkML.h"
#include "PlayState.h"
#include <fstream>
#include <filesystem>
#include <SDL.h>
#include <string>
#include "Laser.h"
#include "Alien.h"
#include "Bunker.h"
#include "ShooterAlien.h"
#include "Mothership.h"
#include "Ufo.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "Game.h"
#include "SceneObject.h"
#include "Cannon.h"
using namespace std;

/*
PlayState::~PlayState()
{
	delete mothership;
	delete infoBar;
}
*/

/// GAME LOGIC BLOCK:
/// muestra el menú inicial e inicializa los GameObjects y el tablero acorde a él, después va el bucle principal del juego
/// con llamadas a los métodos principales, gestiona el framerate y tras acabar el bucle ppal la puntuación por consola*/
void PlayState::run()
{ 
	infoBar = new InfoBar(Point2D<>(0, WIN_HEIGHT - game->getTexture(spaceship)->getFrameHeight()),
	                      game->getTexture(spaceship), INFOBAR_PADDING, this, game->getRenderer());
	mothership = new Mothership(1, 0, 0, 0, this, 0);
	//exampleInit(); //ejemplo de 4x11
	emptyLists();
    readData("map" + std::to_string(mapLevel), game, true);
	startTime = SDL_GetTicks();
	while (!exit)
	{
		SDL_Event event;
		handleEvent(event);
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
			readData("map" + std::to_string(++mapLevel), game, true);
		}
	}
	cout << "\n*** GAME OVER ***\n" << "*** PUNTUACION FINAL: " << playerPoints << " ***\n";
}

/// recorre los objetos de escena y si alguno ha avisado de que ha muerto, estará en la lista de objetos a borrar
///	estos seran borrados y su memoria liberada, y la lista de objetos a borrar se limpiara
void PlayState::update()
{
	mothership->update();
	for (auto i : sceneObjs) 
		i.update();
	/*
	for (auto i : deleteObjs)
	{
		sceneObjs.erase(i.getIterator());
		delete i;
	}
	*/
	infoBar->update();
	//deleteObjs.clear();
}

/// le aplica al renderer el fondo, la textura de cada objeto de escena y el infobar, y lo presenta en pantalla
void PlayState::render() const
{
	SDL_RenderClear(game->getRenderer());
	game->getTexture(stars)->render(); // el fondo!!!!!! :-)
	for (const auto& i : sceneObjs) // los objetos
		i.render();
	infoBar->render();
	SDL_RenderPresent(game->getRenderer());
}

/// INPUT BLOCK
///	gestiona los diferentes inputs que puede haber:
///	de Cannon (en su propio método, mov lateral y disparar),
///	de guardado (S),
///	de carga (L),
///	de mapa (M)
///	y de salida 
void PlayState::handleEvent(const SDL_Event& event)
{
	//SDL_PollEvent(&event) && 
	while (!exit)
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
					readData("save" + std::to_string(k - '0'), game, false);
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
				readData(mapName, game, true);
			}
		}
		else if (cannon != nullptr) 
			cannon->handleEvent(event);
	}
}

/// genera un tablero ejemplo predeterminado (utilizado principalmente para debugging inicial)
void PlayState::exampleInit() {
	auto it = sceneObjs.begin();
	Point2D<> position;
	SceneObject* object;
	Texture* texture;

	// aliens
	int type = 0;
	texture = game->getTexture(alien);
	for (int i = 0; i < 4; i++)
	{
		if (i == 1 || i == 3)
			type++;
		for (int j = 0; j < 11; j++)
		{
			position = Point2D<>((texture->getFrameWidth() + 3) * j + 130,
			                     (texture->getFrameHeight() + 3) * i + 32);
			//+130 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			/*if (type == 0) 
				object = new ShooterAlien(position, type, texture, game, mothership);
			else 
				object = new Alien(position, type, texture, game, mothership);*/

			//addSceneObject(object);
			mothership->addAlienCount();
		}
	}

	// bunkers
	texture = game->getTexture(bunker);
	for (uint i = 1; i < 5; i++)
	{
		position = Point2D<>(WIN_WIDTH * i / 5 - texture->getFrameWidth() / 2,
		                     WIN_HEIGHT - WIN_HEIGHT / 4.0 - texture->getFrameHeight());
		object = new Bunker(position, 4, texture, this);
		addSceneObject(object);
	}

	// cannon
	texture = game->getTexture(spaceship);
	position = Point2D<>(WIN_WIDTH / 2 - texture->getFrameWidth() / 2,
	                     WIN_HEIGHT - WIN_HEIGHT / 8.0 - texture->getFrameHeight());
	cannon = new Cannon(position, texture, this, 3);
	object = cannon;
	addSceneObject(object);

	// el ufo (IMPORTANTE: puede haber varios)
	position = Point2D<>(WIN_WIDTH, WIN_HEIGHT / 2);
	texture = game->getTexture(ufos);
	object = new Ufo(position, texture, this, false, visible);
	addSceneObject(object);
}

/// DATA MANAGEMENT BLOCK:
///	invoca el método save() de cada objeto y guarda en el stream que se le proporciona sus datos
void PlayState::saveData(const std::string& saveFileName) const {
	std::ofstream out(SAVE_FILE_ROOT + saveFileName + ".txt");
	if (out.fail())
		throw FileNotFoundError("Could not read the save file called "s + saveFileName);
	for (auto i : sceneObjs)
		i.save(out);
	out << "7 " << playerPoints << endl;
	out.close();
}


/// metodo para simplificar la generacion de objetos y los metodos en los que se generan las entidades de los tableros
///	puesto que se llama muchas veces a estas lineas de manera conjunta,
///	realiza el push back, la asignacion del iterador al objeto y actualiza su rectangulo inicialmente
void PlayState::addSceneObject(SceneObject* object)
{ // método para simplificar las inicializaciones del tablero
	const auto it = sceneObjs.end();
	//sceneObjs.push_back(object);
	//object->setAnchor(it);
	object->updateRect();
}


/// metodo para vaciar ambas listas de objetos y liberar su memoria, usado previo a cargar partida o mapa
void PlayState::emptyLists()
{
	//for (auto it = sceneObjs.begin(); it != sceneObjs.end(); ++it)
	/*for (auto i : sceneObjs)
		sceneObjs.erase(i.getAnchor());*/
	/*
	for (auto i : deleteObjs)
		deleteObjs.erase(i.getIterator());
	*/
	sceneObjs.clear();
	//deleteObjs.clear();
}

/// gestiona las colisiones entre el laser dado y cada objeto en la escena
///	devuelve true si ha colisionado con algo y se invocaran a los metodos
/// correspondientes
bool PlayState::damage(const SDL_Rect*& rect, char friendly)  const 
{
	//std::any_of(sceneObjs.begin(), sceneObjs.end(),);
	for (auto i : sceneObjs)
		if (i.hit(rect, friendly))
			return true;
	return false;
}

/// devuelve un numero aleatorio entre min y max
int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<>(min, max)(randomGenerator);
}

/// lee y anyade al juego las diferentes entidades del archivo proporcionado, ya sea mapa o partida guardada
///	para gestionar esto último se utiliza un bool que indica si es mapa o no, para determinar la raíz de directorio
///	que le corresponde
void PlayState::readData(const std::string& filename, Game* juego, bool isMap) {
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
			cannon = new Cannon(position, game->getTexture(spaceship), this, lives, timer);
			object = cannon;
			break;
		}
		case 1: // alien
			cin >> x >> y;
			cin >> type;
			position = Point2D<>(x, y);
			object = new Alien(position, type, game->getTexture(alien), this, mothership);
			mothership->addAlienCount();
			alienCount++;
			break;
		case 2: // shooter alien
			cin >> x >> y;
			cin >> type >> timer;
			position = Point2D<>(x, y);
			object = new ShooterAlien(position, type, game->getTexture(alien), this, mothership, timer);
			mothership->addAlienCount();
			alienCount++;
			break;
		case 3: // mothership
			cin >> x >> y; // para gastarlos
			cin >> state >> level >> timer;
			//mothership.setState(state);
			mothership->setLevel(level);
			mothership->setTimer(timer);
			break;
		case 4: // bunker
			cin >> x >> y;
			cin >> lives;
			position = Point2D<>(x, y);
			object = new Bunker(position, lives, game->getTexture(bunker), this);
			break;
		case 5: // ufo
			cin >> x >> y;
			cin >> y >> state >> timer;
			position = Point2D<>(x, y);
			object = new Ufo(position, game->getTexture(ufos), this, false, state, timer);
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
			addSceneObject(object);
	}
	std::cin.rdbuf(cinbuf); //restablecer entrada
	in.close();
}
