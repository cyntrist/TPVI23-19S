#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState : public GameState
{
	Texture* menuTexture;
public:
	MainMenuState(Game* game);
	void render() const override;
};

