#pragma once
//#include <any>
#include "SDL.h"
#include "texture.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include <vector>
#include <array>
#include <fstream>
#include <random>

using uint = unsigned int;

static constexpr uint WIN_WIDTH = 800,
WIN_HEIGHT = 600,
NUM_TEXTURES = 4;
static const std::string TEXTURE_ROOT = "..\\images\\";
static const std::string MAP_ROOT = "..\\material\\mapas\\";
enum TextureName { stars, spaceship, bunker, alien};
static constexpr double alienMovSpeed = 10;
static constexpr double cannonMovSpeed = 0.1;
static constexpr double laserMovSpeed = 0.05;
const int alienRefreshRate = 1000;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	std::vector<Alien*> aliens; 
	std::vector<Bunker*> bunkers;
	std::vector<Cannon*> cannons;
	std::vector<Laser*> lasers;
	bool exit = false;
	std::array<Texture*, NUM_TEXTURES> textures; 
	int movDir = 1;
	int timer = alienRefreshRate;

	void exampleInit(Game *juego);
	void readMap(const std::string &mapName, Game *juego);
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	int getDirection();
	void cannotMove();
	void fireLaser(Point2D<double>&pos, Vector2D<>&speed, bool friendly);
	int getRandomRange(const int& min, const int& max);
	bool collisions(Laser* laser) const;
};

