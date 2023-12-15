#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState(Game* game) : GameState(game, "PAUSE") {}
	virtual void update() override {};
    virtual void render() const override {};
};

