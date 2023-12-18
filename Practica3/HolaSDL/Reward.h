#pragma once
#include "SceneObject.h"
class Reward : public SceneObject
{
public:
	Reward() = default;
	Reward(Point2D<> _position, Texture* _texture, PlayState* _playState);
	void update() override;
	bool hit(const SDL_Rect* otherRect, char friendly) override { return false;};
	void save(std::ostream& os) const override;
};

