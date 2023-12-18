#include "Ufo.h"

#include "Bomb.h"
#include "Game.h"
#include "PlayState.h"
#include "Cannon.h"
#include "Reward.h"

Ufo::Ufo(Point2D<> p, Texture* t, PlayState* ps, bool d, int s)
	: SceneObject(p, 1, t, ps)
{
	//iniPos = Point2D<>(WIN_WIDTH, position.getY()); // guarda referencia a la posicion incial para poder volver en el futuro
	iniPos = p;
	direction = d ? 1 : -1;
	state = s;
	hiddenTimer = HIDDEN_DURATION;
}

/// constructora con sobrecarga hiddenTimer específico
Ufo::Ufo(Point2D<> position, Texture* texture, PlayState* playState, bool direction, int state, int hT)
	: Ufo(position, texture, playState, direction, state)
{
	hiddenTimer = hT;
}

/// renderiza su frame segun el estado en el que esta, sin salirse 
void Ufo::render() const
{
	texture->renderFrame(rect, 0, std::min(state, texture->getNumColumns()));
}

/// si no esta destruido, gestiona la interseccion entre su rectangulo y otro, y añade la puntuacion predefinida
bool Ufo::hit(const SDL_Rect* otherRect, char friendly)
{
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'r' && state != destroyed)
	{
		playState->addScore(SCORE_POINTS);
		//playState->getCannon()->setInvincible(true); //supongo que esto no hace falta porque ya esta la reward
		lives--;

		// generacion de reward o bomba
		int chance = playState->getRandomRange(0, 3); // 25% de soltar un reward o bomba, 50% de nada (por poner algo)
		if (chance == 0)
		{ // genera bomba
			playState->addSceneObject(new Bomb(position, playState->getGame()->getTexture(bomb), playState)); //al darle al ufo y spawnearse la bomba, el laser colisiona con la bomba antes de ser destruido y le resta una vida a la bomba instantaneamente pero tampoco es que haya tiempo para ponerse a arreglar estos detalles cuando hay cosas mas importantes aun
		}
		else if (chance == 1)
		{ // genera reward
			playState->addSceneObject(new Reward(position, playState->getGame()->getTexture(shield_reward), playState));
		}
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
			hiddenTimer = playState->getRandomRange( 10 * TIME_BETWEEN_FRAMES, 50 * TIME_BETWEEN_FRAMES);
		}
		else hiddenTimer--;
		break;
	default: // nunca se puede dar?? pero lo contemplo por si acaso
		break;
	}
} 