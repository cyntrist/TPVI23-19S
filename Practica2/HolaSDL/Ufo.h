#pragma once
#include "SceneObject.h"

enum states { visible, hidden, destroyed };

class Ufo final: public SceneObject 
{
	int direction;
	int state; 
public:
	Ufo() = default;
	Ufo(Texture* texture, Game* game, int state);
	void render() const override;
	bool update() override;
};