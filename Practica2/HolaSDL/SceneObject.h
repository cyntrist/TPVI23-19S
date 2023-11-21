#pragma once
#include "GameObject.h"

class SceneObject : public GameObject
{
	Point2D<double> position;
	int width, height, lives;	
	Texture* texture; // no se si va en esta clase pero es lo que más sentido me parece que tiene?
	SDL_Rect rect; // idem
	// movida del iterador cuando lleguemos
public:
	virtual void hit(SDL_Rect*& otherRect, char friendly);
	virtual Point2D<double> getPosition() { return position; }
};
