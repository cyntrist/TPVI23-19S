#pragma once
#include <SDL_rect.h>

#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"

class SceneObject : public GameObject
{
	Point2D<double> position;
	int width, height, lives;	
	Texture* texture; // no se si va en esta clase pero es lo que más sentido me parece que tiene?
	SDL_Rect rect; // idem
	// movida del iterador cuando lleguemos
public:
	// getters
	virtual Point2D<double> getPosition() { return position; }
	virtual int getWidth() { return width; }
	virtual int getHeight() { return height; }
	virtual int getLives() { return lives; }
	virtual Texture* getTexture() { return texture; }
	virtual SDL_Rect getRect() { return rect; }
	// methods
	virtual void hit(SDL_Rect*& otherRect, char friendly);
};
