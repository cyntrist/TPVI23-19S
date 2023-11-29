#pragma once
#include "SDL.h"
#include "texture.h"
#include "InfoBar.h"
#include <vector>
#include <array>
#include <list>
#include <random>
#include "Laser.h"
#include "SceneObject.h"
#include "Cannon.h"
class Mothership;

using uint = unsigned int;

constexpr uint WIN_WIDTH = 800,
			  WIN_HEIGHT = 600,
			  NUM_TEXTURES = 5;
constexpr double FRAME_RATE = 60, 
				TIME_BETWEEN_FRAMES = 1000 / FRAME_RATE,
				ALIEN_MOV_SPEED = 1 * TIME_BETWEEN_FRAMES,
				UFO_MOV_SPEED = ALIEN_MOV_SPEED / 10, 
				CANNON_MOV_SPEED = 0.25 * TIME_BETWEEN_FRAMES,
				LASER_MOV_SPEED = 0.5 * TIME_BETWEEN_FRAMES;
constexpr int ALIEN_REFRESH_RATE = 0.5 * FRAME_RATE, //cada cuantos updates del juego queremos que se ejecute el update de los aliens
			  INFOBAR_PADDING = 10, // espacio entre iconos del infobar
			  LEVEL_NUMBER = 4; // cantidad de niveles de juego que hay
const std::string TEXTURE_ROOT = "..\\images\\",
				 MAP_ROOT = R"(..\\maps\\2\\)", // raw string literal
				 SAVE_FILE_ROOT = "..\\";
enum TextureName { stars, spaceship, bunker, alien, ufos};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Texture*, NUM_TEXTURES> textures; 
	std::list<SceneObject*> sceneObjs;
	std::list<SceneObject*> deleteObjs;
	InfoBar* infoBar;
	Mothership* mothership = nullptr;
	Cannon* cannon;
	std::mt19937_64 randomGenerator;


	bool exit = false; // game over
	uint32_t startTime, frameTime; // contadores de tiempo para ticks de framerate
	int playerPoints = 0; // score del jugador
	int mapLevel = 1; // el nivel de juego a cargar (mapk.txt), no debería salirse por encima de LEVEL_NUMBER con los mapas actuales
	inline static int alienUpdateTimer = ALIEN_REFRESH_RATE; // inline para prevenir errores de compilacion por estar definido en el header

	void startMenu();
	void exampleInit();
	void readData(const std::string& saveFileName, Game* juego, bool isMap);
	void saveData(const std::string& saveFileName) const;
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	void endGame() { exit = true; }
	void fireLaser(Point2D<>&pos, Vector2D<int>&speed, char friendly);
	bool damage(Laser* laser) const;
	void addObject(SceneObject*& object);
	void hasDied(const std::list<SceneObject*>::iterator& iterator) {
		deleteObjs.push_back(*iterator);
	}
	void addScore(const int value) {
		playerPoints += value;
	}
	void emptyLists();
	// getters
	int getAlienUpdateTimer() const { return alienUpdateTimer; }
	int getRandomRange(int min, int max);
	int getScore() { return playerPoints; }
	SDL_Renderer* getRenderer() const { return renderer; }
	Cannon* getCannon() const { return cannon; }
};

