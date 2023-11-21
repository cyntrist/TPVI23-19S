#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"
#include "GameObject.h"

class InfoBar : public GameObject
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	Texture* texture = nullptr;
	int padding;
	int points;

public:
	InfoBar() = default;
	InfoBar(const Point2D<double>& position, Texture* texture, int padding);
	void render() const;
};