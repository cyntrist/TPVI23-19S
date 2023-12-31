#pragma once
#include <functional>
#include "SceneObject.h"
using SDLCallback = std::function<void()>;

class Reward : public SceneObject
{
protected:
	SDLCallback callback;
	std::list<SDLCallback> callbacks;

public:
	Reward() = default;
	Reward(Point2D<>, Texture*, PlayState*);
	void update() override;
	bool hit(const SDL_Rect* otherRect, char friendly) override { return false;};
	void save(std::ostream& os) const override;
	void connect(const SDLCallback& newCb)
	{
		callbacks.push_back(newCb);
	}
	void setCallback(SDLCallback newCb)
	{
		callback = newCb;
	}
};

