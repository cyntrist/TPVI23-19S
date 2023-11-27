#include "checkML.h"
#include "Laser.h"
#include "Game.h"

/*Laser::Laser(Point2D<double>& position, Vector2D<>& speed, char color, Game* game)
: SceneObject(position, 1, nullptr, game), speed(speed), color(color) { } //POR ESTO PETAAAAAAAAAAAAAAAAAAAA SE LLAMA AL CONSTRUCTOR DE SCENEOBJECT Y CON LA TEXTURA A NULLPTR, ENTONCES CUANDO ESTE INTENTA SETEAR LA WIDTH Y HEIGHT NO PUEDE AAAAAAAAAAAAAAAAAAAAAAAAA (son las 5 y de repente me ha venido la inspiracion)*/

Laser::Laser(Point2D<double>& p, Vector2D<>& s, char c, Game* g) {
	lives = 1;
	position = p;
	speed = s;
	color = c;
	game = g;
}

void Laser::updateRect()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = LASER_WIDTH;
	rect.h = LASER_HEIGHT;
}

void Laser::render() const 
{
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 255, 255);
	if (color == FRIENDLY_CHAR)
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 0, 255);
	SDL_RenderFillRect(game->getRenderer(), &rect);
}

bool Laser::update() {
	position = position + speed;
	updateRect();
	if (position.getY() < 0) return false;  // si se sale por arriba
	if (lives <= 0 || game->collisions(this))
	{
		std::cout << "me cago en la puta" << std::endl;
	}
	return lives > 0 && !game->collisions(this);
	// llama a las colisiones totales, y si ha colisionado, sera destruido en el propio game
}


bool Laser::hit(SDL_Rect* otherRect, char friendly) {
	if (otherRect != getRect() && SDL_HasIntersection(getRect(), otherRect))
		return true;
	return false;
}