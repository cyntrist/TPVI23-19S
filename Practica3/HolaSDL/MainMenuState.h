#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState : public GameState
{
public:
	MainMenuState() { stateID = "Main Menu"; }
	~MainMenuState() = default;
	void update() override {}
	void render() const override {}
};

