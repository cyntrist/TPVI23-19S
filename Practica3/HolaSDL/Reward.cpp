#include "checkML.h"
#include "Reward.h"

#include "Cannon.h"
#include "PlayState.h"

Reward::Reward(Point2D<> _position, Texture* _texture, PlayState* _playState)
: SceneObject(_position, 1, _texture, _playState)
{

}

void Reward::update()
{
    updateRect();
    position = Vector2D(position.getX(), position.getY() + REWARD_MOV_SPEED);
    SceneObject::update();

    // si ha chocado con el cannon y le ha de dar un reward
    if (playState->mayGrantReward(&rect)) 
    {
    	//callback();
        for (SDLCallback& buttonCallback : callbacks)
				buttonCallback();
    	hasDied();
	}
    // si no ocurre lo anterior y ha salido de la pantalla
	else if (position.getY()  < 0 || position.getY() > WIN_HEIGHT) 
    {
		hasDied();
	}
}
void Reward::save(std::ostream& os) const
{
    os << "9 ";
    SceneObject::save(os);
}
