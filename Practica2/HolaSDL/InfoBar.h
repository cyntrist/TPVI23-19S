#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "GameObject.h"
class Game;

class InfoBar final : public GameObject
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	Texture* texture = nullptr;
	int padding;
	int points;

public:
	InfoBar() = default;
	InfoBar(const Point2D<double>& position, Texture* texture, int padding, Game* game);
	void render() const override;
	void update() override {} // para que no llore por ser virtual puro sin sobreescribir
};
