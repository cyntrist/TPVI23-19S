#include "ShooterAlien.h"
#include "Game.h"

ShooterAlien::ShooterAlien(const Point2D<>& position, int type, Texture* texture, GameState* gameState, Mothership* mothership)
: Alien(position, type, texture, gameState, mothership), reloadTime(0) { }

/// constructora con sobrecarga de reloadTime especifico
ShooterAlien::ShooterAlien(const Point2D<>& position, int type, Texture* texture, GameState* gameState, Mothership* mothership, int reloadTime)
: ShooterAlien(position, type, texture, gameState, mothership)
{
	this->reloadTime = reloadTime;
}

/// metodo para guardar sus datos en el stream proporcionado
void ShooterAlien::save(std::ostream& os) const 
{
	os << "2 ";
	SceneObject::save(os);
	os << type << " " << reloadTime << std::endl;
}

/// descuenta el timer hasta que dispara en intervalos aleatorios, ademas de que invoca al update de su padre Alien para movimientos
void ShooterAlien::update()
{
	/*if (reloadTime <= 0)
		reloadTime = gameState->getRandomRange(2 * TIME_BETWEEN_FRAMES, 20 * TIME_BETWEEN_FRAMES); //IMPORTANTE: el min y max son numero de frames de update del alien, es decir, el alien disparara una vez cada x updates entre ese rango
	else
		reloadTime--;
	*/
	if (reloadTime <= 0) { //se que esta feo de narices pero si lo ponia dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion (supongo que iniciando los aliens ya con un valor del random se solucionaria, pero no conseguia hacerlo)
		Point2D<> pos(position.getX() + (texture->getFrameWidth() - LASER_WIDTH) / 2, position.getY() + texture->getFrameHeight());
		Vector2D<int> speed(0, 0.5 * LASER_MOV_SPEED);
		//gameState->fireLaser(pos, speed, 'b');
	}
	Alien::update();
}