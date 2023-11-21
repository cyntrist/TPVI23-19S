#pragma once
#include "Game.h"

class GameObject
{
	Game* game = nullptr;
public:
	virtual ~GameObject() = delete;
	virtual void render() = 0;
	virtual bool update() = 0;
	virtual void save() = 0;
};
