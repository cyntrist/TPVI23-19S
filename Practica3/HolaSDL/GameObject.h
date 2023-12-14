#pragma once
#include <ostream>
#include "gameList.h"
#include "GameState.h"
class Game;
class GameState;
class GameObject
{
protected:
	GameState* gameState = nullptr;
public:
	GameObject() = default;
	GameObject(GameState* gameState) : gameState(gameState) { }
	virtual GameState* getGameState() { return gameState; } 
	virtual ~GameObject() = default; // destructora 
	virtual void render() const = 0; // para renderizra sprites enteros
	virtual void render(int row, int col) const { } // para renderizar frames concretos
	virtual void update() = 0; // update de cada objeto
	virtual void save(std::ostream& os) const = 0; // para guardar la info de cada objeto?? ni idea bestie
};
