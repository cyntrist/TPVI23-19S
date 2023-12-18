#pragma once
#include "GameState.h"
#include "Button.h"

class EndState : public GameState
{
public:
	EndState(Game* game);
    virtual void render() const {};
};

