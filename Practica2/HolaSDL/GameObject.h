#pragma once
#include <ostream>
class Game;

class GameObject
{
protected:
	Game* game = nullptr;
public:
	GameObject();
	GameObject(Game* game) { this->game = game; }
	virtual Game* getGame() { return game; }
	//virtual ~GameObject() = delete;
	virtual void render() const = 0;
	virtual bool update() = 0;
	virtual void save(std::ostream& os) const = 0;
};
