﻿#pragma once
#include "SDL.h"
#include "texture.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include <vector>
#include <array>
#include <random>

using uint = unsigned int;

static constexpr uint WIN_WIDTH = 800,
					  WIN_HEIGHT = 600,
					  NUM_TEXTURES = 4;
static const std::string TEXTURE_ROOT = "..\\images\\",
						 MAP_ROOT = "..\\material\\mapas\\";
static constexpr double FRAME_RATE = 60, 
						TIME_BETWEEN_FRAMES = 1000 / FRAME_RATE,
						ALIEN_MOV_SPEED = 1 * TIME_BETWEEN_FRAMES,
						CANNON_MOV_SPEED = 0.25 * TIME_BETWEEN_FRAMES,
						LASER_MOV_SPEED = 0.15 * TIME_BETWEEN_FRAMES;
static constexpr int ALIEN_REFRESH_RATE = 0.5 * FRAME_RATE; //cada cuantos updates del juego queremos que se ejecute el update de los aliens
enum TextureName { stars, spaceship, bunker, alien};

static constexpr double
alienMovSpeed = 1 * TIME_BETWEEN_FRAMES,
cannonMovSpeed = 0.25 * TIME_BETWEEN_FRAMES,
laserMovSpeed = 0.15 * TIME_BETWEEN_FRAMES;

const int alienRefreshRate = 0.5 * FRAME_RATE; //cada cuantos updates del juego queremos que se ejecute el update de los aliens

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
	int alienUpdateTimer = ALIEN_REFRESH_RATE;
	uint32_t startTime, frameTime;
	int playerPoints = 0;

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

