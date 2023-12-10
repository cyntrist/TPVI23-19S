#pragma once
#include "GameState.h"
#include "SceneObject.h"

class PlayState : public GameState
{
protected:
    GameList<SceneObject> sceneObjs;
public:
    bool damage(SDL_Rect, char);
    int getRandomRange(int, int);
    void hasDied(GameList<SceneObject>::anchor);
};

