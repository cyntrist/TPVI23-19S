#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState() : GameState("PAUSE") {}
	virtual void update() {};
    virtual void render() {};
};

