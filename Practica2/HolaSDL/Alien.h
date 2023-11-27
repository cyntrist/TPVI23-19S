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
	Mothership* mothership;

public:
	Alien() = default;
	Alien(const Point2D<double>& position, int type, Texture* texture, Game* game);
	Alien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership);
	bool update() override;
	void render() const override;
	void down();
	int getType() const { return type; }
	bool hit(SDL_Rect* otherRect, char friendly) override;
};
