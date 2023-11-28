#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <SDL_ttf.h>
#include <string>
class Game;

const std::string FONT_ROOT = "fonts\\font.ttf";

class InfoBar : public GameObject
{
private:
	Point2D<> position = Point2D<>(0, 0);
	Texture* cannonTexture = nullptr; // textura del cannon
	int padding; // margen entre texturas del cannon
	int points = 0; // score
	SDL_Renderer* renderer; // referencia de render de game
	TTF_Font* font = TTF_OpenFont(FONT_ROOT.c_str(), 24); // fuente para el score
	SDL_Color color = { 255, 255, 255 , 100}; // color para score

public:
	InfoBar() = default;
	InfoBar(const Point2D<>& position, Texture* texture, int padding, Game* game, SDL_Renderer* renderer);
	void render() const override;
	void update() override; 
	void save(std::ostream& os) const override {}
};
