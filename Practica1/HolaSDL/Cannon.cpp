#include "Cannon.h"
#include "Game.h"

Cannon::Cannon(const Point2D<double>& p, Texture*& t, Game*& g) {
	position = p;
	texture = t;
	game = g;
	movement = 0;
	startTime = 0;
}

void Cannon::render()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();	
	texture->renderFrame(rect, texture->getNumRows() - 1, texture->getNumColumns() - 1);
}

bool Cannon::update()
{
	if (lives <= 0) return false;

	position = position + Vector2D<>(CANNON_MOV_SPEED * movement, 0);
	if (position.getX() < 0)
		position = Vector2D<>(0, position.getY());
	if (position.getX() > WIN_WIDTH - texture->getFrameWidth())
		position  = Vector2D<>(WIN_WIDTH - texture->getFrameWidth(), position.getY());

	return true;
}

void Cannon::hit()
{
	lives--;
}

void Cannon::handleEvent(const SDL_Event& event)
{
	const auto elapsedTime = SDL_GetTicks() - startTime; 
	if (event.type == SDL_KEYDOWN)
	{ // input general
		if (event.key.keysym.sym == SDLK_RIGHT)
			movement = 1; // movimiento der
		else if (event.key.keysym.sym == SDLK_LEFT)
			movement = -1; // movimiento izq
		else if (event.key.keysym.sym == SDLK_SPACE && elapsedTime >= TIMERMS)
		{ // disparar si han pasado suficientes ticks
			Point2D<double> pos(position.getX() + (texture->getFrameWidth() -LASER_WIDTH)/2, position.getY() - texture->getFrameHeight());
			game->fireLaser(pos, Vector2D<>(0, -LASER_MOV_SPEED), true);
			startTime = SDL_GetTicks(); // se resetea el timer a 0
		}
	}
	else if (event.type == SDL_KEYUP)
		movement = 0; // se para
}


