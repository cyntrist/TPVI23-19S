#include "Cannon.h"
#include "Game.h"

Cannon::Cannon(const Point2D<double>& p, const uint& l, Texture*& t, Game*& g) {
	position = p;
	lives = l;
	texture = t;
	game = g;
	movement = 0;
	timer = 0; //?
}

void Cannon::render()
{
	SDL_Rect rect;
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();	
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

void Cannon::update()
{
	position = position + Vector2D<>(cannonMovSpeed * movement, 0);
	if (position.getX() < 0)
		position = Vector2D<>(0, position.getY());
	if (position.getX() > WIN_WIDTH - texture->getFrameWidth())
		position  = Vector2D<>(WIN_WIDTH - texture->getFrameWidth(), position.getY());

}

void Cannon::hit()
{
	lives--;
}

void Cannon::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
			movement = 1; 
		else if (event.key.keysym.sym == SDLK_LEFT)
			movement = -1;
		else if (event.key.keysym.sym == SDLK_SPACE)
		{ 
			const Point2D<double> pos(position.getX() + (texture->getFrameWidth() -LASER_WIDTH)/2, position.getY() - texture->getFrameHeight());
			game->fireLaser(pos, Vector2D<>(0, -laserMovSpeed), true); 
		}
	}
	else if (event.type == SDL_KEYUP)
		movement = 0;
}


