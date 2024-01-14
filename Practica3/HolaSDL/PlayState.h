#pragma once
#include <array>
#include "GameState.h"
#include "SceneObject.h"
#include <random>
#include "InfoBar.h"
#include <array>
#include <random>
#include "Game.h"
class SceneObject;
class Mothership;
class Cannon;
class Alien;
using uint = unsigned int;

constexpr int	INFOBAR_PADDING = 10, // espacio entre iconos del infobar
				LEVEL_NUMBER = 4, // cantidad de niveles de juego que hay
				// MOVEMENT SPEEDS
				ALIEN_MOV_SPEED = 1 * TIME_BETWEEN_FRAMES,
				UFO_MOV_SPEED = 0.3 * TIME_BETWEEN_FRAMES, 
				CANNON_MOV_SPEED = 0.25 * TIME_BETWEEN_FRAMES,
				LASER_MOV_SPEED = 0.5 * TIME_BETWEEN_FRAMES,
				BOMB_MOV_SPEED = 0.2 * TIME_BETWEEN_FRAMES,
                REWARD_MOV_SPEED = 0.2 * TIME_BETWEEN_FRAMES;

class PlayState : public GameState
{
protected:
    GameList<SceneObject> sceneObjects;
	InfoBar* infoBar;
	Mothership* mothership;
	Cannon* cannon;
	std::mt19937_64 randomGenerator;
	uint32_t startTime, frameTime; // contadores de tiempo para ticks de framerate
	int playerPoints = 0; // score del jugador
	int mapLevel = 1; // el nivel de juego a cargar (mapk.txt), no deberia salirse por encima de LEVEL_NUMBER con los mapas actuales

	void exampleInit();
	bool readData(const std::string& saveFileName, Game* juego, bool isMap);
	void saveData(const std::string& saveFileName) const;
public:
	PlayState(Game*, int, bool);
	void addSceneObject(SceneObject* object);
	void handleEvent(const SDL_Event&) override;
	void render() const override;
	void update() override;
	void save(const std::string& fileName) const override { saveData(fileName); }
    bool mayGrantReward(SDL_Rect* rect) const;

	int getRandomRange(int min, int max);
	void hasDied(const GameList<SceneObject>::anchor& anchor)
    {
		sceneObjects.erase(anchor); // vamos a probar si funciona asi
    }
	void endGame() const
	{
		game->exitGame();
	}
	void addScore(const int value)
	{
		playerPoints += value;
	}
    bool damage(SDL_Rect* rect, char friendly) const;

	// getters
	int getScore() const
	{
		return playerPoints;
	}
	Cannon* getCannon() const
	{
		return cannon;
	}
	Game* getGame() const
	{
		return game;
	}
};

