#pragma once
#include <ostream>
class Game;
class GameState;
#include "GameList.h"
class GameObject
{
protected:
	GameState* gameState = nullptr;
	GameList<GameObject, true>::anchor anchor; // interador identificador
public:
	GameObject() = default;
	GameObject(GameState* gameState) : gameState(gameState) { }
	virtual GameState* getGameState() { return gameState; } 
	virtual ~GameObject() = default; // destructora 
	virtual void render() const = 0; // para renderizra sprites enteros
	virtual void render(int row, int col) const { } // para renderizar frames concretos
	virtual void update() = 0; // update de cada objeto
	virtual void save(std::ostream& os) const = 0; 
	GameList<GameObject, true>::anchor getAnchor() const { return anchor; }
	void setListAnchor(GameList<GameObject, true>::anchor value) { anchor = value; }
};
