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
	int state = 0; // estado de animacion
	bool destroy = false; // si ha de ser destruido
	Mothership* mothership;

public:
	Alien() = default;
	Alien(const Point2D<double>& position, int type, Texture* texture, Game* game);

	void render();

	void down();
	int getType() const { return type; }
};
