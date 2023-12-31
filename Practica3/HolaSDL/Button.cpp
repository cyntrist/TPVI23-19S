#include "checkML.h"
#include "Button.h"
#include "Vector2D.h"

Button::Button(Vector2D<>position, Texture* texture) : GameObject(), position(position), texture(texture)
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
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
	/*int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);*/
	SDL_GetMouseState(&mousePoint.x, &mousePoint.y);

	//if	  (mouseX < position.getX() + texture->getFrameWidth() 
	//	&& mouseX > position.getX()
	//	&& mouseY < position.getY() + texture->getFrameHeight() 
	//	&& mouseY > position.getY()) 
	if (SDL_PointInRect(&mousePoint, &rect)) 
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
			for (SDLCallback& buttonCallback : callbacks)
				buttonCallback();
		}
	}
}

void Button::Connect(SDLCallback newCb) {
	callbacks.push_back(newCb);
}

