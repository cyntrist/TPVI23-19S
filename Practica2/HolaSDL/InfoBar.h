#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "GameObject.h"
class Game;

class InfoBar : public GameObject
{
private:
	Point2D<> position = Point2D<>(0, 0);
	Texture* texture = nullptr;
	int padding;
	int points;

public:
	InfoBar() = default;
	InfoBar(const Point2D<>& position, Texture* texture, int padding, Game* game);
	void render() const override;
	void update() override; 
	void save(std::ostream& os) const override {}
};
