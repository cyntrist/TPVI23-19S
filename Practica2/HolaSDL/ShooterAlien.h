#pragma once
#include "Alien.h"
class ShooterAlien final : public Alien
{
private:
	int reloadTime;
public:
	ShooterAlien() = default;
	ShooterAlien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership);
	ShooterAlien(const Point2D<double>& position, int type, Texture* texture, Game* game, Mothership* mothership, int reloadTime);
	bool update() override;
};