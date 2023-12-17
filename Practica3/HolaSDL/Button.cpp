#include "Button.h"

#include "Vector2D.h"

Button::Button(Vector2D<>position, Texture* texture) : GameObject(), position(position), texture(texture)
{
	//m_currentFrame = MOUSE_OUT; // start at frame 0 /// Nuestros botones no tienen hover ni nada asi que no hace falta esto creo
}

void Button::render() const
{
	SDL_Rect rect = {
		position.getX(),
		position.getY(),
		texture->getFrameWidth(),
		texture->getFrameHeight()
	};
	texture->render(rect);
}

void Button::update() 
{
	//Vector2D mousePos; //TheInputHandler::Instance()->getMousePosition(); <-- deberiamos hacer un singleton como este?? XD
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	if	  (mouseX < position.getX() + texture->getFrameWidth() 
		&& mouseX > position.getX()
		&& mouseY < position.getY() + texture->getFrameHeight() 
		&& mouseY > position.getY())
	{
		buttonPos = MOUSE_OVER;
	}
	else
	{
		buttonPos = MOUSE_OUT;
	}

}

void Button::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		if (buttonPos == MOUSE_OVER) {
			for (const SDLCallback& buttonCallback : callbacks)
				buttonCallback(event);
		}
	}
}

void Button::Connect(SDLCallback newCb) {
	callbacks.push_back(newCb);
}

