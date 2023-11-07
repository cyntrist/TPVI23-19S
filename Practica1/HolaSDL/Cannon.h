#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la l�nea de arriba)

using uint = unsigned int;
static constexpr int TIMERMS = 500; // ticks entre disparo y disparo
inline int lives = 3; // est�tica porque, aunque haya varios cannon comparten vidas y as� se lleva f�cil al infobar

class Cannon
{
private:
	Point2D<double> position;
	Texture* texture = nullptr;
	Game* game = nullptr;
	SDL_Rect rect;
	int movement; // direccion de movimiento
	uint startTime; // para el cooldown del cannon

public:
	Cannon() = default;
	Cannon(const Point2D<double>& p, Texture*& t, Game*& g);
	static int getLives() { return lives; }
	SDL_Rect* getRect() { return &rect; }
	void render();
	bool update();
	void hit();
	void handleEvent(const SDL_Event& event);
};