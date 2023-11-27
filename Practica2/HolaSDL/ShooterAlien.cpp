#include "ShooterAlien.h"

#include "Game.h"

ShooterAlien::ShooterAlien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership)
: Alien(position, type, texture, game, mothership), reloadTime(0) { }

ShooterAlien::ShooterAlien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership, int reloadTime)
: ShooterAlien(position, type, texture, game, mothership)
{
	this->reloadTime = reloadTime;
}

bool ShooterAlien::update()
{
	if (reloadTime <= 0)
		reloadTime = game->getRandomRange(2 * TIME_BETWEEN_FRAMES, 20 * TIME_BETWEEN_FRAMES); //IMPORTANTE: el min y max son numero de frames de update del alien, es decir, el alien disparara una vez cada x updates entre ese rango
	else
		reloadTime--;

	if (reloadTime <= 0) { //se que esta feo de narices pero si lo ponia dentro de la comprobacion anterior todos los aliens disparaban en la primera iteracion (supongo que iniciando los aliens ya con un valor del random se solucionaria, pero no conseguia hacerlo)
		Point2D<double> pos(position.getX() + (texture->getFrameWidth() - LASER_WIDTH) / 2, position.getY() + texture->getFrameHeight());
		Vector2D<> speed(0, LASER_MOV_SPEED);
		game->fireLaser(pos, speed, 'b');
	}
	return Alien::update();
}