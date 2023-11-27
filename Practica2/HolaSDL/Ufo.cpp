#include "Ufo.h"
#include "Game.h"

Ufo::Ufo(Point2D<double> p, Texture* t, Game* g, bool d, int s)
{
	position = p;
	iniPos = p; // guarda referencia a la posicion incial para poder volver en el futuro
	lives = 1;
	texture = t;
	game = g;
	direction = d ? 1 : -1;
	state = s;
}

void Ufo::render() const
{
	texture->renderFrame(rect, 0, std::min(state, texture->getNumColumns()));
}

bool Ufo::update()
{
	updateRect();
	switch (state)
	{
	case visible:
		position = position + Vector2D<>(direction * UFO_MOV_SPEED, 0); //movimiento de los aliens
		if (getPosition().getX() + width < 0)
			state = hidden;
		else if (lives <= 0)
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
			hiddenTimer = HIDDEN_DURATION;
		}
		else hiddenTimer--;
		break;
	}
	return true;
}

bool Ufo::hit(SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r' && state != destroyed)
	{
		game->addScore(SCORE_POINTS);
		lives--;
		return true;
	} 
	return false; 
}