#pragma once
#include "GameState.h"
#include "SceneObject.h"
#include <random>
#include "Cannon.h"
class Game;

class PlayState : public GameState
{
protected:
    GameList<SceneObject*> sceneObjs;
    GameList<SceneObject*> deleteObjs;
    Cannon* cannon;
	std::mt19937_64 randomGenerator;
public:
    PlayState() : randomGenerator(time(nullptr)) {}
    bool damage(const SDL_Rect*& rect, char friendly) const;
    int getRandomRange(int min, int max);
    void hasDied(GameList<SceneObject*>::anchor anchor)
    {
	    //deleteObjs.push_back(anchor);
    };
    /* VERSION ANTIGUA:
	void hasDied(const std::list<SceneObject*>::iterator& iterator) {
		deleteObjs.push_back(*iterator);
	} */
};

