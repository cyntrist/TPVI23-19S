#include "checkML.h"
#include "Cannon.h"
#include "Game.h"
#include "Laser.h"
#include "PlayState.h"
Cannon::Cannon(const Point2D<>& position, Texture* texture, PlayState* _playState, int lives)
	: SceneObject(position, lives, texture, _playState), movement(0), shootTimer(SHOOT_TIMER), invincibleTimer(INVENCIBILITY_TIMER)
{
	SDL_SetTextureBlendMode(texture->getTexture(), SDL_BLENDMODE_ADD);
}

/// constructora sobrecargada con el tiempo preciso
Cannon::Cannon(const Point2D<>& _position, Texture* _texture, PlayState* _playState, int _lives, int _shootTimer)
	: Cannon(_position, _texture, _playState, _lives)
{
	shootTimer = _shootTimer;
	invincibleTimer = INVENCIBILITY_TIMER;
	SDL_SetTextureBlendMode(texture->getTexture(), SDL_BLENDMODE_ADD);
}

/// avisa a game si ha muerto para ser borrado y actualiza su posicion segun la direccion,
///	sin salirse de la pantalla, actualizando su rectangulo
///	tambien contempla si es invencible y rebaja su temporizador, ademas del de disparo
void Cannon::update()
{
	if (lives <= 0) {
		playState->hasDied(sceneObjsAnchor);
		playState->endGame(); //asumo que solo va a haber un cannon
	}

	position = position + Vector2D(CANNON_MOV_SPEED * movement, 0);
	if (position.getX() < 0)
		position = Point2D<>(0, position.getY());
	if (position.getX() > WIN_WIDTH - texture->getFrameWidth())
		position  = Vector2D<>(WIN_WIDTH - texture->getFrameWidth(), position.getY());
	updateRect();

	if (shootTimer > 0)
		shootTimer--;

	if (invincible)
	{
		if (invincibleTimer <= 0)
		{
			invincibleTimer = INVENCIBILITY_TIMER;
			invincible = false;
		} 
		else
		{
			SDL_SetTextureColorMod(texture->getTexture(), 255, 180, 50);
			invincibleTimer--;
		}
	}
	else
	{
		SDL_SetTextureColorMod(texture->getTexture(), 255, 255, 255);
	}
}

/// gestiona el movimiento lateral y el disparo segun las teclas pulsadas
void Cannon::handleEvent(const SDL_Event& event)
{
	const SDL_Keycode key = event.key.keysym.sym;
	if (event.type == SDL_KEYDOWN)
	{ // input general
		if (key == SDLK_RIGHT)
			movement = 1; // movimiento der
		else if (key == SDLK_LEFT)
			movement = -1; // movimiento izq
		else if (key == SDLK_SPACE && shootTimer <= 0)
		{ // disparar si han pasado suficientes ticks
			Point2D<> pos(position.getX() + (texture->getFrameWidth() - LASER_WIDTH) / 2, position.getY() - texture->getFrameHeight());
			Vector2D speed(0, -LASER_MOV_SPEED);
			auto* laser = new Laser(pos, speed, 'r', playState);
			playState->addGameObject(laser);
			playState->addSceneObject(laser);
			shootTimer = SHOOT_TIMER; // se resetea el timer a 0
		}
	}
	else if (event.type == SDL_KEYUP)
		movement = 0; // se para
}

/// gestiona si intersecta con otro objeto
bool Cannon::hit(const SDL_Rect* otherRect, char friendly) {
	if (SDL_HasIntersection(getRect(), otherRect) && friendly == 'b')
	{
		if (!invincible)
		{
			lives--;
			invincible = true;
		}
		return true;
	}
	return false;
}

/// metodo para guardar sus datos en el stream proporcionado
void Cannon::save(std::ostream& os) const 
{
	os << "0 ";
	SceneObject::save(os);
	os << lives << " " << shootTimer << std::endl;
}