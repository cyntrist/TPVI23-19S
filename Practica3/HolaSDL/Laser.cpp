#include "checkML.h"
#include "Laser.h"
#include "Game.h"

Laser::Laser(Point2D<>& p, Vector2D<int>& s, char c, GameState* g) {
	width = LASER_WIDTH;
	height = LASER_HEIGHT;
	lives = 1;
	position = p;
	speed = s;
	color = c;
	gameState = g;
}

/// actualiza su rectangulo
void Laser::updateRect()
{
	rect.x = position.getX();
	rect.y = position.getY();
	rect.w = LASER_WIDTH;
	rect.h = LASER_HEIGHT;
}

/// crea un rectangulo del color especificado en su SDL_rect
void Laser::render() const 
{
	SDL_Renderer* renderer = gameState->getGame()->getRenderer();
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	if (color == FRIENDLY_CHAR)
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &rect);
}

/// metodo para guardar sus datos en el stream proporcionado
void Laser::save(std::ostream& os) const 
{
	os << "6 ";
	SceneObject::save(os);
	os << color << std::endl;
}

/// avisa al game de que ha muerto si tiene interseccion con otros objetos,
/// no le quedan vidas o si se sale por los bordes de la ventana
void Laser::update() {
	position = position + speed;
	updateRect();
	/*if (gameState->damage(this) || lives <= 0 || position.getY()  < 0 || position.getY() > WIN_HEIGHT)
		gameState->hasDied(anchor);*/
}

/// gestiona la interseccion entre su rectangulo y otro
bool Laser::hit(const SDL_Rect* otherRect, char friendly) {
	if (otherRect != getRect() && SDL_HasIntersection(getRect(), otherRect))
	{
		lives--;
		return true;
	}
	return false;
}