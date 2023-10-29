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

using uint = unsigned int;

static constexpr uint WIN_WIDTH = 800,
					  WIN_HEIGHT = 600,
					  NUM_TEXTURES = 4;
static const std::string TEXTURE_ROOT = "..\\images\\";
static enum TextureName { stars, spaceship, bunker, aliens};

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	//std::vector<std::any> elements; // me estoy fumando un petardaco
	std::vector<Alien*> aliens; 
	std::vector<Bunker*> bunkers;
	std::vector<Cannon*> cannons;
	std::vector<Laser*> lasers;
	bool exit = false;
	std::array<Texture*, NUM_TEXTURES> textures; 
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
	void getDirection();
	void cannotMove();
	void fireLaser();
};

