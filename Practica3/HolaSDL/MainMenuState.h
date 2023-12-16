#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState : public GameState
{
	Texture* menuTexture;
public:
	MainMenuState(Game* game);
	//~MainMenuState() override = default;
    void update() override;
	void render() const override;
	void handleEvent(const SDL_Event&) override;
};

