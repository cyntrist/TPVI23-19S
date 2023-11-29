#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la l�nea de arriba)

constexpr int TIMER = 100; // duracion del cooldown y factor de invencibilidad

class Cannon : public SceneObject
{
private:
	int movement; // direccion de movimiento
	int shootTimer; // para el cooldown del cannon
	int invincibleTimer; // duracion de invencibilidad
	bool invincible = false; // si es invencible ahora
public:
	Cannon() = default;
	Cannon(const Point2D<>& position, Texture* texture, Game* game, int lives);
	Cannon(const Point2D<>& position, Texture* texture, Game* game, int lives, int startTime);
	void handleEvent(const SDL_Event& event);
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(SDL_Rect* otherRect, char friendly) override;
};