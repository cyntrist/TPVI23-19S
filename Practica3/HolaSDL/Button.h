#pragma once
#include <functional>

#include "GameObject.h"
#include "EventHandler.h"
#include "texture.h"
#include "Vector2D.h"


/// Nuestros botones no tienen hover ni nada asi que no hace falta esto creo
using SDLCallback = std::function<void()>;

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class Button : public GameObject, public EventHandler
{
protected:
	Vector2D<> position;
	SDL_Point mousePoint;	// posicon DEL RATON
	SDL_Rect rect;	// rectangulo DEL BOTON
    Texture* texture;
	button_state buttonPos;
	// callback(s)
	std::list<SDLCallback> callbacks;

public:
	Button() = default;
	Button(Vector2D<> position, Texture* texture);
	void render() const override;
	void update() override;
	void save(std::ostream& os) const override {}
	void handleEvent(const SDL_Event& event) override;
	void Connect(SDLCallback cb);
};

