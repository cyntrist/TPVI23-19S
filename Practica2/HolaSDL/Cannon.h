#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la l�nea de arriba)

using uint = unsigned int;
constexpr int TIMERMS = 500; // ticks entre disparo y disparo

class Cannon
{
private:
	int movement; // direccion de movimiento
	uint startTime; // para el cooldown del cannon
public:
	Cannon() = default;
	Cannon(const Point2D<double>& position, Texture* texture, Game* game);
	Cannon(const Point2D<double>& position, Texture* texture, Game* game, int _lives);
	int getLives() { return lives; }
	const SDL_Rect* getRect() const { return &rect; }
	void handleEvent(const SDL_Event& event);
};