#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState() : GameState("PAUSE") {}
	virtual void update() override {};
    virtual void render() const override {};
};

