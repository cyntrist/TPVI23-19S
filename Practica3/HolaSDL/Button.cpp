#include "Button.h"

#include "Vector2D.h"

Button::Button(Vector2D<>position, Texture* texture) : GameObject(), position(position), texture(texture)
{
	//m_currentFrame = MOUSE_OUT; // start at frame 0 /// Nuestros botones no tienen hover ni nada asi que no hace falta esto creo
}

void Button::render() const
{
	//GameObject::render(); // use the base class drawing
	SDL_Rect rect = { position.getX(), position.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
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
		std::cout << "oleeee";
		//currentFrame = MOUSE_OVER;
		if (true) // TheInputHandler::Instance()->getMouseButtonState(LEFT) <-- si click derecho encima
		{
			//...
		}
	}
	else
	{
		//m_currentFrame = MOUSE_OUT;
	}
}
