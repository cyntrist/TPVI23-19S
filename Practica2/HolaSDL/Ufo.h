#pragma once
#include "SceneObject.h"

constexpr int ANIMATION_DURATION = 10, // los frames que dura destruido
			  HIDDEN_DURATION = 50,  // ESTO DEBERÍA SER O RANDOM O PROVISTO POR EL ARCHIVO pero lo mantenemos para debug
			  SCORE_POINTS = 100;
enum states { visible, destroyed, hidden };

class Ufo final: public SceneObject 
{
	int direction;
	int state;
	int animationTimer = ANIMATION_DURATION;
	int hiddenTimer = HIDDEN_DURATION;
	Point2D<double> iniPos;

public:
	Ufo() = default;
	Ufo(Point2D<double> position, Texture* texture, Game* game, bool direccion, int state);
	void render() const override;
	bool update() override;
	bool hit(SDL_Rect* otherRect, char friendly) override;
};