#pragma once
#include <SDL_rect.h>
#include <iterator>
#include <list>
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
class Game;

class SceneObject : public GameObject
{
protected:
	Point2D<> position;
	int width, height, lives;	
	Texture* texture; // no se si va en esta clase pero es lo que m�s sentido me parece que tiene?
	SDL_Rect rect; // idem
	std::list<SceneObject*>::iterator iterator; // interador identificador
public:
	// constructor
	SceneObject() = default;
	SceneObject(Point2D<> position, int lives, Texture* texture, Game* game);
	// getters
	Point2D<> getPosition() const { return position; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getLives() const { return lives; }
	Texture* getTexture() const { return texture; }
	SDL_Rect* getRect() { return &rect; }
	std::list<SceneObject*>::iterator getIterator() { return iterator;}
	// setter
	void setIterator(const std::list<SceneObject*>::iterator& value) { iterator = value; }
	// methods
	void render() const override;
	void save(std::ostream& os) const override;
	void update() override;
	virtual void updateRect();
	virtual bool hit(SDL_Rect* otherRect, char friendly);
};
