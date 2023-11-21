#pragma once
#include "Laser.h"
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
#include "Mothership.h"
class Game;

using uint = unsigned int;

class Alien : public SceneObject
{
private:
	int type;
	Texture* texture = nullptr;
	Game* game = nullptr;
	int state = 0; // estado de animacion
	SDL_Rect rect; // rectangulo de hitbox
	bool destroy = false; // si ha de ser destruido
	Mothership* mothership;

public:
	Alien() = default;
	Alien(const Point2D<double>& position, int type, Texture* texture, Game* game);
	void render();
	bool update() override;
	void hit() { destroy = true; }
	SDL_Rect* getRect() { return &rect; }
	void down();
	Point2D<double> getPos() { return getPosition(); }
	int getType() const { return type; }
};
