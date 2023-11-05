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
static constexpr double alienMovSpeed = 5,
cannonMovSpeed = 5,
laserMovSpeed = 3,
FRAME_RATE = 16.6; //tiempo que queremos entre cada frame en milisegundos, no numero de frames por segundo (para eso: FRAME_RATE = 1000ms/numfps)
const int alienRefreshRate = 10; //cada cuantos updates del juego queremos que se ejecute el update de los aliens



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
	int alienUpdateTimer = alienRefreshRate;
	uint32_t startTime, frameTime;

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

