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

public:
	Laser() = default;
	Laser(Point2D<>& position, Vector2D<int>& speed, char friendly, Game* game);
	void update() override;
	void updateRect() override;
	void render() const override;
	void save(std::ostream& os) const override;
	char getColor() const { return color; }
	bool hit(SDL_Rect* otherRect, char friendly) override;
};
