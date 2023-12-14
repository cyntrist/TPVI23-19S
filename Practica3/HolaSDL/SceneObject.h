#pragma once
#include <SDL_rect.h>
#include "GameObject.h"
#include "texture.h"
#include "Vector2D.h"
class PlayState;
class Game;
class SceneObject : public GameObject
{
protected:
	Point2D<> position;
	int width, height, lives;	
	Texture* texture; // no se si va en esta clase pero es lo que m�s sentido me parece que tiene?
	SDL_Rect rect; // idem
	PlayState* playState; // para acceder a los métodos únicos de PlayState
	GameList<SceneObject>::anchor sceneObjsAnchor; // interador identificador
public:
	// constructor
	SceneObject() = default;
	SceneObject(Point2D<> position, int lives, Texture* texture, PlayState* playState);
	// getters
	Point2D<> getPosition() const { return position; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getLives() const { return lives; }
	Texture* getTexture() const { return texture; }
	SDL_Rect* getRect() { return &rect; }
	GameList<SceneObject>::anchor getSceneObjsAnchor() const { return sceneObjsAnchor; }
	// methods
	void render() const override;
	void save(std::ostream& os) const override;
	void update() override;
	virtual void updateRect();
	virtual bool hit(const SDL_Rect* otherRect, char friendly);
	void setListAnchor(GameList<SceneObject>::anchor value) { GameObject::setListAnchor(value->elem->getAnchor()); sceneObjsAnchor = value; }
};
