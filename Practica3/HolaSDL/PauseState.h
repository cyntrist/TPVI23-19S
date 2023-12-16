#pragma once
#include "Button.h"
#include "GameState.h"
class PauseState : public GameState
{
public:
	PauseState(Game* game);
	virtual void update() override;
    virtual void render() const override;
	void handleEvent(const SDL_Event&) override;
};

