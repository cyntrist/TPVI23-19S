#include "checkML.h"
#include "Button.h"
#include "Vector2D.h"
const std::string FONT_ROOT = "..\\fonts\\font.ttf";

Button::Button(Vector2D<> position, Texture* texture)
	: GameObject(), position(position), texture(texture)
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

Button::Button(Vector2D<> position, std::string text, SDL_Renderer* renderer)
	: GameObject(), position(position)
{
	font = new Font(FONT_ROOT, 24);
	texture = font->generateTexture(renderer, text, color);
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}

Button::Button(Vector2D<> position, std::string text, SDL_Color color, SDL_Renderer* renderer)
	: Button(position, text, renderer)
{
	this->color = color;
}

Button::~Button()
{
	delete font;
	delete texture;
	GameObject::~GameObject();
}

void Button::render() const
{
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
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		if (buttonPos == MOUSE_OVER)
		{
			for (SDLCallback& buttonCallback : callbacks)
				buttonCallback();
		}
	}
}

void Button::connect(SDLCallback newCb)
{
	callbacks.push_back(newCb);
}

void Button::setPosition(Vector2D<> value)
{
	position = value;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();
}
