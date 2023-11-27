#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la l�nea de arriba)

using uint = unsigned int;
constexpr int TIMERMS = 500; // ticks entre disparo y disparo

class Cannon final : public SceneObject
{
private:
	int movement; // direccion de movimiento
	uint startTime; // para el cooldown del cannon
	int cannonLives = lives; // para el infobar, pero creo que se puede implementar con las vidas normales
public:
	Cannon() = default;
	Cannon(const Point2D<double>& position, Texture* texture, Game* game);
	Cannon(const Point2D<double>& position, Texture* texture, Game* game, int lives);
	Cannon(const Point2D<double>& position, Texture* texture, Game* game, int lives, int startTime);
	void handleEvent(const SDL_Event& event) override;
	bool update() override;
	bool hit(SDL_Rect* otherRect, char friendly) override;
};