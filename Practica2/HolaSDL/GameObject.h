#pragma once
#include <ostream>
class Game;

class GameObject
{
	Game* game = nullptr;
public:
	virtual ~GameObject() = delete;
	virtual void render() const = 0;
	virtual bool update() = 0;
	virtual void save(std::ostream& os) const = 0;
};
