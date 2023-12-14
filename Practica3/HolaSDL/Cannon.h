#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "PlayState.h"
class Game; 

constexpr int SHOOT_TIMER = 10, // duracion del cooldown 
			  INVENCIBILITY_TIMER = 300; // duracion de la invencibilidad

class Cannon : public SceneObject
{
private:
	int movement; // direccion de movimiento
	int shootTimer; // para el cooldown del cannon
	int invincibleTimer; // duracion de invencibilidad
	bool invincible = false; // si es invencible ahora
public:
	Cannon() = default;
	Cannon(const Point2D<>& position, Texture* texture, PlayState* playState, int lives);
	Cannon(const Point2D<>& position, Texture* texture, PlayState* playState, int lives, int shootTimer);
	void handleEvent(const SDL_Event& event);
	void update() override;
	void save(std::ostream& os) const override;
	bool hit(const SDL_Rect* otherRect, char friendly) override;
	void setInvincible(bool value) { invincible = value; }
};