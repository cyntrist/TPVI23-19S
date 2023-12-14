#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
//#include "Game.h"
class Game; // para evitar dependencia circular (la linea de arriba)

constexpr int SHOOT_TIMER = 10, // duracion del cooldown 
			  INVENCIBILITY_TIMER = 300; // duracion de la invencibilidad

class Cannon : public SceneObject, EventHandler
{
private:
	int movement; // direccion de movimiento
	int shootTimer; // para el cooldown del cannon
	int invincibleTimer; // duracion de invencibilidad
	bool invincible = false; // si es invencible ahora
public:
	Cannon() = default;
	Cannon(const Point2D<>& position, Texture* texture, Game* game, int lives);
	Cannon(const Point2D<>& position, Texture* texture, Game* game, int lives, int shootTimer);
	void handleEvent(const SDL_Event& event);
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(const SDL_Rect* otherRect, char friendly) override;
	void setInvincible(bool value) { invincible = value; }
};