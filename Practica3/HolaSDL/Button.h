#pragma once
#include <functional>

#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include "Vector2D.h"

/// Nuestros botones no tienen hover ni nada asi que no hace falta esto creo
/*
enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};
*/
class Button : public GameObject, public EventHandler
{
protected:
	Vector2D<> position; // creo que deberia heredar de sceneobject, pero si el enunciado dice que no..
    Texture* texture;
	// callback(s)
public:
	Button(); //= default;
	//Button(...);
	void render() const override;
	void update() override;
};

