#pragma once
#include "SDL.h"
#include "texture.h"
#include "GameStateMachine.h"
#include <array>
class Mothership;

constexpr int NUM_TEXTURES = 18; // cantidad de texturas a cargar
const std::string TEXTURE_ROOT = "..\\images\\",
			  MAP_ROOT = R"(..\\maps\\2\\)", // raw string literal
			  SAVE_FILE_ROOT = "..\\";
enum TextureName
{
	stars, spaceship, bunker, aliens, ufos, bomb, shield, shield_reward,
	btn_cargar, btn_continuar, btn_guardar, btn_nueva, btn_salir, btn_volver,
	codigo, game_over, has_ganado, menu
};
class Game {
private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::array<Texture*, NUM_TEXTURES> textures;
	GameStateMachine* stateMachine;
	bool exit = false;
public:
	Game();
	~Game();
	void run();
	void handleEvents();
	SDL_Renderer* getRenderer() const { return renderer; }
	Texture* getTexture(TextureName name) const { return textures[name]; }
	SDL_Renderer* getRenderer() { return renderer; }
};

