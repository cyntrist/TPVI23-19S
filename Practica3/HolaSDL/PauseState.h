#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState(Game* game);
	//void render() const override;
	//void handleEvent(const SDL_Event&) override;
};

