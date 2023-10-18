#pragma once

#include <any>
#include "SDL.h"
#include "texture.h"
#include <vector>
#include <array>

#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"

using uint = unsigned int;

constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_TEXTURES = 3;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<std::any> elements; // de qué tipo????
	//std::vector<Alien, Bunker, Cannon, Laser> elements;
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

