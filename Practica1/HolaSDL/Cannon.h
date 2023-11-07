#pragma once
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la línea de arriba)

using uint = unsigned int;
static constexpr int TIMERMS = 500; // ticks entre disparo y disparo
inline int lives = 1; // inline porque aunque haya varios cannon comparten vidas y se lleva fácil al infobar
					  // (y estatica no lo traduce bien cuando accede? preguntar al profe cómo se debería hacer esto)

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
	Cannon(const Point2D<double>& position, Texture*& texture, Game*& game);
	Cannon(const Point2D<double>& position, Texture*& texture, Game*& game, const int& _lives);
	static int getLives()  { return lives; }
	const SDL_Rect* getRect() const { return &rect; }
	void render();
	bool update();
	static void hit() { lives--; }
	void handleEvent(const SDL_Event& event);
	Point2D<double> getPos() const {
		return position;
	}
};