#include "checkML.h"
#include "Mothership.h"
#include "PlayState.h"
#include <fstream>
#include <filesystem>
#include <SDL.h>
#include <string>
#include "Laser.h"
#include "Alien.h"
#include "Bunker.h"
#include "ShooterAlien.h"
#include "Ufo.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "Game.h"
#include "SceneObject.h"
#include "Cannon.h"
#include "EndState.h"
#include "PauseState.h"
using namespace std;

PlayState::PlayState(Game* game) : GameState(game, "PLAY"), randomGenerator(time(nullptr)) //idea, meter un param mas en este constructor para saber cuando cargar un mapa, un archivo de guardado o lo que sea (basicamente un int con un switch y a chuparla, apunto esto para que no se me olvide mas tarde)
{
	startTime = SDL_GetTicks();
	mothership = new Mothership(1, 0, 0, 0, this, 0);
	infoBar = new InfoBar(Point2D<>(0, WIN_HEIGHT - game->getTexture(spaceship)->getFrameHeight()),
	                      game->getTexture(spaceship), INFOBAR_PADDING, this, game->getRenderer());
	//if (!readData("map" + std::to_string(mapLevel), game, true))
		exampleInit();

	addGameObject(infoBar);
	addGameObject(mothership);
}

/// GAME LOGIC BLOCK:
/// recorre los objetos de escena y si alguno ha avisado de que ha muerto, estara en la lista de objetos a borrar
///	estos seran borrados y su memoria liberada, y la lista de objetos a borrar se limpiara
void PlayState::update()
{
	frameTime = SDL_GetTicks() - startTime;
	if (frameTime > TIME_BETWEEN_FRAMES)
	{
		GameState::update();
		infoBar->setPoints(playerPoints);
		infoBar->setLives(cannon->getLives());
		startTime = SDL_GetTicks();
		
		if (mothership->getAlienCount() <= 0)
		{
			mapLevel = mapLevel % LEVEL_NUMBER;
			game->getStateMachine()->replaceState(new PlayState(game)); // vamos a ver si esto es una manera inteligente de resetearlo
		}

		if (cannon->getLives() <= 0)
			game->getStateMachine()->replaceState(new EndState(game)); // vamos a ver si esto es una manera inteligente de resetearlo
	}
}

/// le aplica al renderer el fondo, la textura de cada objeto de escena y el infobar, y lo presenta en pantalla
void PlayState::render() const
{
	game->getTexture(stars)->render(); // el fondo!!!!!! :-)
	GameState::render();
}

/// INPUT BLOCK
///	gestiona los diferentes inputs que puede haber:
///	de Cannon (en su propio metodo, mov lateral y disparar),
///	de guardado (S),
///	de carga (L),
///	de mapa (M)
///	y de salida 
void PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

	SDL_Keycode key = event.key.keysym.sym;
    if (event.type == SDL_KEYDOWN && (key == SDLK_ESCAPE))
		game->getStateMachine()->pushState(new PauseState(game));
}

/// genera un tablero ejemplo predeterminado (utilizado principalmente para debugging inicial)
void PlayState::exampleInit() {
	auto it = sceneObjects.begin();
	Point2D<> position;
	SceneObject* object;
	Texture* texture;

	// aliens
	int type = 0;
	texture = game->getTexture(aliens);
	for (int i = 0; i < 4; i++)
	{
		if (i == 1 || i == 3)
			type++;
		for (int j = 0; j < 11; j++)
		{
			position = Point2D<>((texture->getFrameWidth() + 3) * j + 130,
			                     (texture->getFrameHeight() + 3) * i + 32);
			//+130 para que esten centrados, +32 para que no aparezcan arriba del todo y +3 para que no esten pegados entre ellos
			if (type == 0) 
				object = new ShooterAlien (position, type, texture, this, mothership);
			else 
				object = new Alien(position, type, texture, this, mothership);
			addSceneObject(object);
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
	addEventListener(cannon);

	// el ufo (IMPORTANTE: puede haber varios)
	position = Point2D<>(WIN_WIDTH, WIN_HEIGHT / 2);
	texture = game->getTexture(ufos);
	object = new Ufo(position, texture, this, false, visible);
	addSceneObject(object);
}

/// DATA MANAGEMENT BLOCK:
///	invoca el metodo save() de cada objeto y guarda en el stream que se le proporciona sus datos
void PlayState::saveData(const std::string& saveFileName) const {
	std::ofstream out(SAVE_FILE_ROOT + saveFileName + ".txt");
	if (out.fail())
		throw FileNotFoundError("Could not read the save file called "s + saveFileName);
	for (auto i : sceneObjects)
		i.save(out);
	out << "7 " << playerPoints << endl;
	out.close();
}


/// metodo para simplificar la generacion de objetos y los metodos en los que se generan las entidades de los tableros
///	puesto que se llama muchas veces a estas lineas de manera conjunta,
///	realiza el push back, la asignacion del iterador al objeto y actualiza su rectangulo inicialmente
void PlayState::addSceneObject(SceneObject* object)
{ // método para simplificar las inicializaciones del tablero
	addGameObject(object);
	sceneObjects.push_back(object);
	object->updateRect();
}

/// gestiona las colisiones entre el laser dado y cada objeto en la escena
///	devuelve true si ha colisionado con algo y se invocaran a los metodos
/// correspondientes
bool PlayState::damage(SDL_Rect* rect, char friendly) const 
{
	//std::any_of(sceneObjects.begin(), sceneObjects.end(),);
	for (auto& i : sceneObjects)
		if (i.hit(rect, friendly))
			return true;
	return false;
}

/// devuelve un numero aleatorio entre min y max
int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<>(min, max)(randomGenerator);
}

/// lee y anyade al juego las diferentes entidades del archivo proporcionado, ya sea mapa o partida guardada
///	para gestionar esto ultimo se utiliza un bool que indica si es mapa o no, para determinar la raíz de directorio
///	que le corresponde
bool PlayState::readData(const std::string& filename, Game* juego, bool isMap) {
	string fileroot;
	if (!isMap) fileroot = SAVE_FILE_ROOT + filename + ".txt";
	else fileroot = MAP_ROOT + filename + ".txt";
	std::ifstream in(fileroot);
	const auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to "map name".txt 
	if (in.fail())
		throw FileNotFoundError("Could not read the specified data file at "s + fileroot) ;
	if (in.peek() == std::ifstream::traits_type::eof()) 
		throw FileFormatError("Empty data file: "s + fileroot); 

	auto it = sceneObjects.begin();
	int read, x, y, lives, timer, type, state, level;
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
			addEventListener(cannon);
			break;
		}
		case 1: // alien
			cin >> x >> y;
			cin >> type;
			position = Point2D<>(x, y);
			object = new Alien(position, type, game->getTexture(aliens), this, mothership);
			break;
		case 2: // shooter alien
			cin >> x >> y;
			cin >> type >> timer;
			position = Point2D<>(x, y);
			object = new ShooterAlien(position, type, game->getTexture(aliens), this, mothership, timer);
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
	return true;
}
