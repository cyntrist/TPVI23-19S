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
	std::list<int>::iterator iterator; // movida del iterador (int???)
public:
	// constructor
	SceneObject();
	SceneObject(Point2D<double> position, int lives, Texture* texture, Game* game);
	// getters
	virtual Point2D<double> getPosition() { return position; }
	virtual int getWidth() { return width; }
	virtual int getHeight() { return height; }
	virtual int getLives() { return lives; }
	virtual Texture* getTexture() { return texture; }
	virtual SDL_Rect getRect() { return rect; }
	// setter
	virtual void setListIterator() {} // no se hacer esto!!!!!!!!
	// methods
	void render() const override;
	void render(int row, int col) const override; // para frames
	bool update() override;
	virtual void updateRect();
	virtual void hit(SDL_Rect*& otherRect, char friendly);
	virtual void hasDied();
};
