#pragma once
#include <ostream>
class Game;

class GameObject
{
protected:
	Game* game = nullptr;
public:
	GameObject() = default;
	GameObject(Game* game) : game(game) { }
	virtual Game* getGame() { return game; }
	virtual ~GameObject() = default;
	virtual void render() const = 0; // para renderizra sprites enteros
	virtual void render(int row, int col) const = 0; // para renderizar frames concretos
	virtual bool update() = 0; // update de cada objeto
	virtual void save(std::ostream& os) const = 0; // para guardar la info de cada objeto?? ni idea bestie
};
