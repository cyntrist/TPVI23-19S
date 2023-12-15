#pragma once
#include "GameState.h"
#include "Button.h"
class MainMenuState : public GameState
{
	Texture* texture;
	Button* button1;
public:
	MainMenuState(Texture* menuTexture, Texture* button1);
	//~MainMenuState() override = default;
    void update() override;
	void render() const override;
};

