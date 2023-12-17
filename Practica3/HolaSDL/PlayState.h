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

constexpr int	ALIEN_REFRESH_RATE = 0.5 * FRAME_RATE, //cada cuantos updates del juego queremos que se ejecute el update de los aliens
				INFOBAR_PADDING = 10, // espacio entre iconos del infobar
				LEVEL_NUMBER = 4, // cantidad de niveles de juego que hay
				// MOVEMENT SPEEDS
				ALIEN_MOV_SPEED = 1 * TIME_BETWEEN_FRAMES,
				UFO_MOV_SPEED = 0.3 * TIME_BETWEEN_FRAMES, 
				CANNON_MOV_SPEED = 0.25 * TIME_BETWEEN_FRAMES,
				LASER_MOV_SPEED = 0.5 * TIME_BETWEEN_FRAMES;

class PlayState : public GameState
{
protected:
    GameList<SceneObject> sceneObjs;
	InfoBar* infoBar;
	Mothership* mothership;
	Cannon* cannon;
	std::mt19937_64 randomGenerator;
	uint32_t startTime, frameTime; // contadores de tiempo para ticks de framerate
	int playerPoints = 0; // score del jugador
	int mapLevel = 1; // el nivel de juego a cargar (mapk.txt), no deberia salirse por encima de LEVEL_NUMBER con los mapas actuales

	void exampleInit();
	void readData(const std::string& saveFileName, Game* juego, bool isMap);
	void saveData(const std::string& saveFileName) const;
public:
	PlayState(Game* game);
	//~PlayState() override;
	//void addEventListener() override;
	void addSceneObject(SceneObject* object);
	void handleEvent(const SDL_Event&) override;
	void render() const override;
	void update() override;
	void run();
	int getRandomRange(int min, int max);
	void hasDied(const GameList<SceneObject>::anchor& anchor)
    {
		sceneObjs.erase(anchor); // vamos a probar si funciona asi
    }
	void endGame()
	{
		game->exitGame();
	}
	void addScore(const int value)
	{
		playerPoints += value;
	}
	void emptyLists();
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
};

