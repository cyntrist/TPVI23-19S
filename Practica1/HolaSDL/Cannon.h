#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la línea de arriba)

using uint = unsigned int;
static constexpr int TIMERMS = 200;

class Cannon
{
private:
	Point2D<double> position;
	Texture* texture = nullptr;
	Game* game = nullptr;
	SDL_Rect rect;

	int movement; 	
	int lives;
	uint startTime; // para el cooldown del cañon

public:
	Cannon() = default;
	Cannon(const Point2D<double>& p, const uint& l, Texture*& t, Game*& g);
	SDL_Rect* getRect() { return &rect; }
	void render();
	bool update();
	void hit();
	void handleEvent(const SDL_Event& event);
};