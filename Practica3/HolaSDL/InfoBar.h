#pragma once
#include "texture.h"
#include "Vector2D.h"
#include "GameObject.h"
#include <SDL_ttf.h>
#include <string>
#include <fstream>
#include "Font.h"
class Game;

const std::string FONT_ROOT = "..\\fonts\\font.ttf";

class InfoBar : public GameObject
{
private:
	Point2D<> position = Point2D<>(0, 0);
	Texture* cannonTexture = nullptr; // textura del cannon
	int padding; // margen entre texturas del cannon
	int lives; // las vidas del cannon

	Font* font = new Font(FONT_ROOT, 24);
	int points = 0; // score
	SDL_Renderer* renderer; // referencia de render de game
	SDL_Color color = { 255, 255, 255 , 255}; // color para score

public:
	InfoBar() = default;
	InfoBar(const Point2D<>& position, Texture* texture, int padding, GameState* gameState, SDL_Renderer* renderer);
	~InfoBar() override;
	void render() const override;
	void update() override {};
	void setPoints(int value) {
		points = value;
	}
	void setLives(int value)
	{
		lives = value;
	}
	void save(std::ostream& os) const override {}

};
