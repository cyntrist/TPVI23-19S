#pragma once
//#include <any>
#include "SDL.h"
#include "texture.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include <vector>
//#include <array>

using uint = unsigned int;

constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_TEXTURES = 3;
constexpr std::string TEXTURE_ROOT = "";

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	//std::vector<std::any> elements; // me estoy fumando un petardaco
	std::vector<Alien*> aliens; // me dan error alien y canon exclusivamente no lo entiendo
	std::vector<Bunker*> bunkers;
	std::vector<Cannon*> cannons;
	std::vector<Laser*> lasers;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];
	//std::array<Texture*, NUM_TEXTURES> textures; // tipo 2??
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

