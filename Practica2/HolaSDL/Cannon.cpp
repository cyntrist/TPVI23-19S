#include "checkML.h"
#include "Cannon.h"
#include "Game.h"

Cannon::Cannon(const Point2D<double>& position, Texture* texture, Game* game, int lives)
	: SceneObject(position, lives, texture, game), movement(0), startTime(TIMERMS), cannonLives(lives) { }

Cannon::Cannon(const Point2D<double>& _position, Texture* _texture, Game* _game, int _lives, int _startTime)
	: Cannon(_position, _texture, _game, _lives) { startTime = _startTime; }

void Cannon::update()
{
	if (lives <= 0) {
		game->hasDied(iterator);
		game->endGame(); //asumo que solo va a haber un cannon
	}

	position = position + Vector2D<>(CANNON_MOV_SPEED * movement, 0);
	if (position.getX() < 0)
		position = Vector2D<>(0, position.getY());
	if (position.getX() > WIN_WIDTH - texture->getFrameWidth())
		position  = Vector2D<>(WIN_WIDTH - texture->getFrameWidth(), position.getY());
	updateRect();
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
			Point2D<double> pos(position.getX() + (texture->getFrameWidth() /* - LASER_WIDTH*/) / 2, position.getY() - texture->getFrameHeight());
			Vector2D<> speed(0, -LASER_MOV_SPEED);
			game->fireLaser(pos, speed, 'r');
			startTime = SDL_GetTicks(); // se resetea el timer a 0
		}
	}
	else if (event.type == SDL_KEYUP)
		movement = 0; // se para
}

bool Cannon::hit(SDL_Rect* otherRect, char friendly) {
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'b')
	{ 
		lives--;
		return true;
	}
	return false;
}

