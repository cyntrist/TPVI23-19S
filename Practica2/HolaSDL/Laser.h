#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
class Game;
using uint = unsigned int;
constexpr int LASER_WIDTH = 5,
			  LASER_HEIGHT = 30;

class Laser : SceneObject
{
private:
	Vector2D<> speed;
	char color;
	SDL_Rect rect;
	bool destroy = false; // si ha de ser destruido

public:
	Laser() = default;
	Laser(Point2D<double>& position, Vector2D<>& speed, bool friendly, Game* game);
	char getColor() const { return color; }

};
