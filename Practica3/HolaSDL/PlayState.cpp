#include "checkML.h"
#include "PlayState.h"
#include "Game.h"

/// metodo para vaciar ambas listas de objetos y liberar su memoria, usado previo a cargar partida o mapa
void PlayState::emptyLists()
{
	for (const auto i : sceneObjs)
		delete i;
	sceneObjs.clear();
	for (const auto i : deleteObjs)
		delete i;
	deleteObjs.clear();
}

/// gestiona las colisiones entre el laser dado y cada objeto en la escena
///	devuelve true si ha colisionado con algo y se invocarán a los métodos
/// correspondientes
bool PlayState::damage(const SDL_Rect*& rect, char friendly)  const 
{
	//std::any_of(sceneObjs.begin(), sceneObjs.end(),);
	for (auto const i : sceneObjs)
		if (i->hit(rect, friendly))
			return true;
	return false;
}

/// devuelve un número aleatorio entre min y max
int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<>(min, max)(randomGenerator);
}