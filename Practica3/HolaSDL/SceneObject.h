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
	GameList<SceneObject*>::anchor anchor; // interador identificador
public:
	// constructor
	SceneObject() = default;
	SceneObject(Point2D<> position, int lives, Texture* texture, GameState* gameState);
	// getters
	Point2D<> getPosition() const { return position; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getLives() const { return lives; }
	Texture* getTexture() const { return texture; }
	const SDL_Rect* getRect() const { return &rect; }
	GameList<SceneObject*>::anchor getAnchor() const { return anchor;}
	// setter
	void setAnchor(const GameList<SceneObject*>::anchor& value) { anchor = value; }
	// methods
	void render() const override;
	void save(std::ostream& os) const override;
	void update() override;
	virtual void updateRect();
	virtual bool hit(const SDL_Rect* otherRect, char friendly);
};
