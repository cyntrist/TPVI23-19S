#pragma once
#include "SceneObject.h"
class Game;

constexpr int ANIMATION_DURATION = 10, // los frames que dura destruido
			  HIDDEN_DURATION = 100,  // solo para debugging
			  SCORE_POINTS = 100; // la puntuacion que proporciona eliminarlo

enum states { visible, destroyed, hidden };

class Ufo : public SceneObject 
{
	int direction; // direccion que sigue (usualmente va a ser a la izq (-1))
	int state; // estado del ufo
	int animationTimer = ANIMATION_DURATION; // temporizador de duracion de explosion al eliminarlo
	int hiddenTimer; // duracion aleatoria que tarda en reaparecer
	Point2D<> iniPos; // posicion inicial a la que devolverlo cuando se sale por la izq o es destruido

public:
	Ufo() = default;
	Ufo(Point2D<> position, Texture* texture, Game* game, bool direction, int state);
	Ufo(Point2D<> position, Texture* texture, Game* game, bool direction, int state, int hT);
	void render() const override;
	bool hit(const SDL_Rect* otherRect, char friendly) override;
	void update() override;
	void save(std::ostream& os) const override;
};