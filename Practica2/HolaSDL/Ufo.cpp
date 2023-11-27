#include "Ufo.h"
#include "Game.h"


Ufo::Ufo(Texture* t, Game* g, int s)
{
	lives = 1;
	texture = t;
	game = g;
	direction = -1;
	state = s;
	position = Point2D<double>(WIN_WIDTH + texture->getFrameWidth(), texture->getFrameHeight());
}

void Ufo::render() const
{
	texture->renderFrame(rect, 0, state);
}

bool Ufo::update()
{
	switch (state)
	{
	case visible:
		position = position + Vector2D<>(direction * ALIEN_MOV_SPEED, 0); //movimiento de los aliens
		if (getPosition().getX() < 0 - texture->getFrameWidth())
			state = hidden;
		if (lives <= 0)
			return false;
		break;
	case hidden:
		break;
	case destroyed:
		// ha de mostrar el frame de explosion (de ello se encarga el render) durane unos segundos y luego volver al estado hidden además de devolverlo a la posición inicial
		break;
	}
	return true;
}