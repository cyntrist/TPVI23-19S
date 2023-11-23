#pragma once
#include "SceneObject.h"

//enum state { visible, hidden, destroyed};

class Ufo : public SceneObject
{
	int state; //int?
public:
	Ufo();
	Ufo(int state);
	bool update() override;
};
