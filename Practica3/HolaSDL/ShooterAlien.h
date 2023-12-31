#pragma once
#include "Alien.h"
class Game;

class ShooterAlien : public Alien
{
private:
	int reloadTime;
public:
	ShooterAlien() = default;
	ShooterAlien(const Point2D<>& position, int type, Texture* texture, PlayState* playState, Mothership* mothership);
	ShooterAlien(const Point2D<>& position, int type, Texture* texture, PlayState* playState, Mothership* mothership, int reloadTime);
	void update() override;
	void save(std::ostream& os) const override;
};