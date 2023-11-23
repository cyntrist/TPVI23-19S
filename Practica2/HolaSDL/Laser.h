#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
class Game;
using uint = unsigned int;
constexpr int LASER_WIDTH = 5,
			  LASER_HEIGHT = 30;
constexpr char FRIENDLY_CHAR = 'r';

class Laser : public SceneObject
{
private:
	Vector2D<> speed;
	char color;
	bool destroy = false; // si ha de ser destruido

public:
	Laser() = default;
	Laser(Point2D<double>& position, Vector2D<>& speed, char friendly, Game* game);
	bool update() override;
	void updateRect() override;
	void render(SDL_Renderer& renderer) const;
	char getColor() const { return color; }
};
