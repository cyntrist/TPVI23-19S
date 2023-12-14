#pragma once
#include "GameState.h"
#include "Button.h"

class EndState : public GameState
{
    EndState() { stateID = "End State";  }
	virtual void update() {};
    virtual void render() const {};
};

