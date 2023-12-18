#include "checkML.h"
#include "Reward.h"

#include "Cannon.h"
#include "PlayState.h"

Reward::Reward(Point2D<> _position, Texture* _texture, PlayState* _playState) : SceneObject(_position, 1, _texture, _playState)
{

}

void Reward::update()
{
    updateRect();
    position = Vector2D<>(position.getX(), position.getY() + REWARD_MOV_SPEED);
    SceneObject::update();
    if(SDL_HasIntersection(getRect(), playState->getCannon()->getRect()))
    {
        playState->getCannon()->setInvincible(true);
        hasDied();
    }
}
