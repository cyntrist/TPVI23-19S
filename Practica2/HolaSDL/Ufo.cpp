#include "Ufo.h"
#include "Game.h"

Ufo::Ufo(Point2D<> p, Texture* t, Game* g, bool d, int s)
	: SceneObject(p, 1, t, g)
{
	iniPos = position; // guarda referencia a la posicion incial para poder volver en el futuro
	direction = d ? 1 : -1;
	state = s;
	hiddenTimer = HIDDEN_DURATION;
}
Ufo::Ufo(Point2D<> position, Texture* texture, Game* game, bool direction, int state, int hT)
	: Ufo(position, texture, game, direction, state)
{
	hiddenTimer = hT;
}

void Ufo::render() const
{
	texture->renderFrame(rect, 0, std::min(state, texture->getNumColumns()));
}

bool Ufo::hit(SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r' && state != destroyed)
	{
		Game::addScore(SCORE_POINTS);
		lives--;
		return true;
	} 
	return false; 
}

void Ufo::update()
{ // todo: todo XD
	updateRect();
	switch (state)
	{
	case visible:
		position = position + Vector2D<>(direction * UFO_MOV_SPEED, 0); //movimiento de los aliens
		if (getPosition().getX() + width < 0)
			state = hidden;
		if (lives <= 0)
		{
			state = destroyed;
			lives = 1;
		}
		break;
	case destroyed:
		// ha de mostrar el frame de explosion (de ello se encarga el render) durane unos segundos y luego volver al estado hidden adem�s de devolverlo a la posici�n inicial
		if (animationTimer <= 0)
		{
			state = hidden;
			position = iniPos;
			animationTimer = ANIMATION_DURATION;
		}
		else animationTimer--;
		break;
	case hidden:
		if (hiddenTimer <= 0)
		{
			state = visible;
			position = iniPos;
			hiddenTimer = game->getRandomRange( 10 * TIME_BETWEEN_FRAMES, 50 * TIME_BETWEEN_FRAMES);
		}
		else hiddenTimer--;
		break;
	}
}