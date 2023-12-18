#pragma once
#include "SceneObject.h"
class Bomb : public SceneObject
{
public:
	Bomb() = default;
	Bomb(Point2D<> _position, Texture* _texture, PlayState* _playState);
	void update() override;
	bool hit(const SDL_Rect* otherRect, char friendly) override;
	void save(std::ostream& os) const override;
};

