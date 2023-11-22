#include "ShooterAlien.h"

ShooterAlien::ShooterAlien(const Point2D<double>& p, int ty, Texture* te, Game* g, Mothership* m, int reloadTime)
: Alien(p, ty, te, g), reloadTime(reloadTime) { }
