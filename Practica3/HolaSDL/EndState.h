#pragma once
#include "GameState.h"
#include "Button.h"

class EndState : public GameState
{
public:
	EndState() : GameState("END") {}
	virtual void update() {};
    virtual void render() const {};
};

