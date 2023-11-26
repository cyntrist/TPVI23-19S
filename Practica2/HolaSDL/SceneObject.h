#pragma once
#include <SDL_rect.h>
#include <iterator>
#include <list>
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"

class SceneObject : public GameObject
{
protected:
	Point2D<double> position;
	int width, height, lives;	
	Texture* texture; // no se si va en esta clase pero es lo que más sentido me parece que tiene?
	SDL_Rect rect; // idem
	std::list<SceneObject*>::iterator iterator; // movida del iterador (int???)
public:
	// constructor
	SceneObject();
	SceneObject(Point2D<double> position, int lives, Texture* texture, Game* game);
	// getters
	Point2D<double> getPosition() const { return position; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getLives() const { return lives; }
	Texture* getTexture() const { return texture; }
	SDL_Rect* getRect() { return &rect; }//Cynthia reina
	std::list<SceneObject*>::iterator getIterator() { return iterator;}
	// setter
	void setIterator(const std::list<SceneObject*>::iterator& value) { iterator = value; }
	// methods
	void render() const override;
	bool update() override;
	virtual void handleEvent(const SDL_Event& event) {}
	virtual void updateRect();
	virtual bool hit(SDL_Rect* otherRect, char friendly);
	virtual bool hasDied();
};
