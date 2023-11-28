#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "SceneObject.h"
class Game;

class Bunker : public SceneObject
{
public:
	Bunker() = default;
	Bunker(const Point2D<>& position, int lives, Texture* texture, Game* game);
	void render() const override;
	void update() override;
};