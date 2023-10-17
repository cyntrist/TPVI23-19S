#pragma once

#include "SDL.h"
#include "texture.h"

using uint = unsigned int;

constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_TEXTURES = 3;

class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	bool exit = false;
	Texture* textures[NUM_TEXTURES];
public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
};

