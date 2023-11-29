#include "Ufo.h"
#include "Game.h"

Ufo::Ufo(Point2D<> p, Texture* t, Game* g, bool d, int s)
	: SceneObject(p, 1, t, g)
{
	//iniPos = Point2D<>(WIN_WIDTH, position.getY()); // guarda referencia a la posicion incial para poder volver en el futuro
	iniPos = p;
	direction = d ? 1 : -1;
	state = s;
	hiddenTimer = HIDDEN_DURATION;
}

/// constructora con sobrecarga hiddenTimer específico
Ufo::Ufo(Point2D<> position, Texture* texture, Game* game, bool direction, int state, int hT)
	: Ufo(position, texture, game, direction, state)
{
	hiddenTimer = hT;
}

/// renderiza su frame segun el estado en el que esta, sin salirse 
void Ufo::render() const
{
	texture->renderFrame(rect, 0, std::min(state, texture->getNumColumns()));
}

/// si no esta destruido, gestiona la interseccion entre su rectangulo y otro, y añade la puntuacion predefinida
bool Ufo::hit(SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r' && state != destroyed)
	{
		game->addScore(SCORE_POINTS);
		game->getCannon()->setInvincible(true);
		lives--;
		return true;
	} 
	return false; 
}

/// metodo para guardar sus datos en el stream proporcionado
void Ufo::save(std::ostream& os) const 
{ // no tiene sentido imprimir la altura dos veces, pero como en los mapas lo hace pues lo hago aqui tambien 
	os << "5 ";
	SceneObject::save(os);
	os << position.getY() << " " << state << " " << hiddenTimer << std::endl;
}

/// maquina de estados, actualiza el rectangulo y si esta visible se mueve
///	si esta visible y ha sido destruido cambia su estado acorde a ello y el render realiza la animacion
///	tambien reestablece su vida
///	destroyed y hidden tienen sus respectivos contadores de tiempo para animarlos o hacerlos desaparecer
///	un intervalo aleatorio, respectivamente ademas de devolverlo a su posicion inicial
void Ufo::update()
{ 
	updateRect();
	switch (state)
	{
	case visible:
		if (hiddenTimer <= 0) // esta comprobacion para cuando se leen de archivo con estado 0 (visible) y espera concretas
			position = position + Vector2D(direction * UFO_MOV_SPEED, 0); 
		else hiddenTimer--;
		
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
	default: // nunca se puede dar?? pero lo contemplo por si acaso
		break;
	}
} 