#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
    PauseState() { stateID = "Pause State";  }
	virtual void update() {};
    virtual void render() {};
};

