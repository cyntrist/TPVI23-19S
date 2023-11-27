#pragma once
#include "SceneObject.h"

constexpr int ANIMATION_DURATION = 10, // los frames que dura destruido
			  HIDDEN_DURATION = 100,  // solo para debugging
			  SCORE_POINTS = 100; // la puntuación que proporciona eliminarlo

enum states { visible, destroyed, hidden };

class Ufo final: public SceneObject 
{
	int direction;
	int state;
	int animationTimer = ANIMATION_DURATION;
	int hiddenTimer;
	Point2D<double> iniPos;

public:
	Ufo() = default;
	Ufo(Point2D<double> position, Texture* texture, Game* game, bool direction, int state);
	Ufo(Point2D<double> position, Texture* texture, Game* game, bool direction, int state, int hT);
	void render() const override;
	bool update() override;
	bool hit(SDL_Rect* otherRect, char friendly) override;
};