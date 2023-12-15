#include "checkML.h"
#include "Game.h"
#include <filesystem>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Laser.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "SDLError.h"
#include "PlayState.h"

using namespace std;

/// estructura para las texturas
struct sprite { 
	std::string name;
	int rows;
	int cols;
};

/// array de estructuras con las texturas que queremos usar
const sprite sprites[NUM_TEXTURES] { 
	sprite {"stars", 1, 1},
	sprite {"spaceship", 1, 1},
	sprite {"bunker", 1, 4},
	sprite {"alien", 3, 2},
	sprite {"ufo", 1, 2},
	sprite {"bomb", 1, 1},
	sprite {"shield", 1, 1},
	sprite {"shield_reward", 1, 1},
	sprite {"btn_cargar", 1, 1},
	sprite {"btn_continuar", 1, 1},
	sprite {"btn_guardar", 1, 1},
	sprite {"btn_nueva", 1, 1},
	sprite {"btn_salir", 1, 1},
	sprite {"btn_volver", 1, 1},
	sprite {"codigo", 1, 1},
	sprite {"game_over", 1, 1},
	sprite {"has_ganado", 1, 1},
	sprite {"menu", 1, 1}
};

/// constructora de Game, inicializa las texturas, SDL y renderer
Game::Game() { 
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw SDLError("Error loading SDL window or renderer. "s + SDL_GetError());
	for (int i = 0; i < NUM_TEXTURES; i++)
	textures[i] = new Texture(renderer, (TEXTURE_ROOT + sprites[i].name + ".png").c_str(), sprites[i].rows, sprites[i].cols);
	SDL_RenderClear(renderer);
	stateMachine = new GameStateMachine();
	stateMachine->replaceState(new PauseState(this));
}

/// destructora de Game, borra la memoria dinámica, el renderer y la ventana y cierra le juego
Game::~Game() {
	delete stateMachine;
	for (const auto i : textures)
		delete i;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit && stateMachine->getStackSize() > 0)
	{
		SDL_RenderClear(renderer);
		stateMachine->render();
		stateMachine->update();
		handleEvents();
		SDL_RenderPresent(renderer);
	}
}

void Game::handleEvents()
{ // entiendo que a través de esto se escuchará a eventos de cambio de estado que emitan los propios estados
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		SDL_Keycode key = event.key.keysym.sym; 
		if (event.type == SDL_QUIT) 
			exit = true;
		else
		{
			if (event.type == SDL_KEYDOWN && key == SDLK_s) // en vez de esto, listeners?
			{
				if (stateMachine->getStateID() == "MENU")
					stateMachine->replaceState(new PauseState(this));
				else
					stateMachine->replaceState(new MainMenuState(this));
			}
		}
		/* VERSION ANTIGUA:
		SDL_Keycode key = event.key.keysym.sym;
		if (event.type == SDL_QUIT) exit = true;
		else if (event.type == SDL_KEYDOWN && (key == SDLK_s || key == SDLK_l ||key == SDLK_m))
		{
			if (key == SDLK_s) // guardar
			{
				std::cout << "Input save slot to save to: " << std::endl;
				char k;
				std::cin >> k;
				if (isdigit(k))
				{
					saveData("save" + std::to_string(k - '0'));
					endGame();
					std::cout << "Saved game." << std::endl;
				}
				else std::cout << "Invalid number, resuming game." << std::endl;
			}
			else if (key == SDLK_l)
			{
				std::cout << "Input save slot to load: " << std::endl;
				char k;
				std::cin >> k;
				if (isdigit(k))
				{
					emptyLists();
					readData("save" + std::to_string(k - '0'), this, false);
					std::cout << "Loaded game." << std::endl;
				}
				else std::cout << "Invalid number, resuming game." << std::endl;
			}
			else if (key == SDLK_m)
			{
				cout << "Map name: ";
				std::string mapName;
				cin >> mapName;
				emptyLists();
				readData(mapName, this, true);
			}
		}
		else if (cannon != nullptr) 
				cannon->handleEvent(event);
		*/
	}
}