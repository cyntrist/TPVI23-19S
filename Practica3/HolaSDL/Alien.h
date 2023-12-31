#pragma once
#include "SceneObject.h"
#include "texture.h"
#include "Vector2D.h"
class Mothership;
using uint = unsigned int;

class Alien : public SceneObject
{
protected:
	int type; // que tipo de alien son
	int state = 0; // estado de animacion
	Mothership* mothership; // referencia a la madre nodriza
	int descent; // posicion en el eje y inicial para luego calcular el descenso segun el level de la nave nodriza
	int speed = 1; 
public:
	Alien() = default;
	Alien(const Point2D<>& position, int type, Texture* texture, PlayState* playState, Mothership* mothership);
	void update() override;
	void render() const override;
	void save(std::ostream& os) const override;
	int getType() const { return type; }
	bool hit(const SDL_Rect* otherRect, char friendly) override;
	void setMothership(Mothership* _mothership) { mothership = _mothership; }
};
