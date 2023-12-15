#pragma once
#include "GameState.h"
#include "Button.h"

class EndState : public GameState
{
public:
	EndState(Game* game) : GameState(game, "END") {}
	virtual void update() {};
    virtual void render() const {};
};

