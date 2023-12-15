#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState : public GameState
{
	Texture* texture;
public:
	MainMenuState(Texture*);
	//~MainMenuState() override = default;
    void update() override;
	void render() const override;
};

