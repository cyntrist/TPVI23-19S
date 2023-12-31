#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "Cannon.h"

class InfoBar
{
private:
	Point2D<double> position = Point2D<double>(0, 0);
	Texture* texture = nullptr;
	int padding;

public:
	InfoBar() = default;
	InfoBar(const Point2D<double>& position, Texture*& texture, const int& padding);
	void render() const;
};