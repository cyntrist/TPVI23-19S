#pragma once
#include <array>
#include "GameState.h"
#include "SceneObject.h"
#include <random>
#include "InfoBar.h"
#include <array>
#include <random>
class SceneObject;
class Mothership;
class Cannon;
using uint = unsigned int;

constexpr int	WIN_WIDTH = 800, // ancho de la ventana de juego
				WIN_HEIGHT = 600, // alto de la ventana de juego
				FRAME_RATE = 60, // frecuencia de refresco
				TIME_BETWEEN_FRAMES = 1000 / FRAME_RATE, // tiempo real entre refrescos
				ALIEN_REFRESH_RATE = 0.5 * FRAME_RATE, //cada cuantos updates del juego queremos que se ejecute el update de los aliens
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
    //GameList<SceneObject> deleteObjs; // segun entiendo la lista de tobeerased esta en el propio gamelist y solo hay que hacer erase?
	InfoBar* infoBar;
	Mothership* mothership;
	Cannon* cannon;
	std::mt19937_64 randomGenerator;

	bool exit = false; // game over
	uint32_t startTime, frameTime; // contadores de tiempo para ticks de framerate
	int playerPoints = 0; // score del jugador
	int mapLevel = 1; // el nivel de juego a cargar (mapk.txt), no debería salirse por encima de LEVEL_NUMBER con los mapas actuales

	void exampleInit();
	void readData(const std::string& saveFileName, Game* juego, bool isMap);
	void saveData(const std::string& saveFileName) const;
public:
    PlayState() : randomGenerator(time(nullptr)) { }
	//~PlayState();
	void addEventListener() override;
	void addSceneObject(SceneObject* object);
	void handleEvent(const SDL_Event&) override;
	void render() const override;
	void update() override;
	void run();
	int getRandomRange(int min, int max);
	void hasDied(GameList<GameObject>::anchor anchor)
    {
		//sceneObjs.erase(anchor); // vamos a probar si funciona asi
    }
	void endGame()
	{
		exit = true;
	}
	void addScore(const int value)
	{
		playerPoints += value;
	}
	void emptyLists();
    bool damage(const SDL_Rect*& rect, char friendly) const;

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

