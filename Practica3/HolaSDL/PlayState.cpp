#include "checkML.h"
#include "PlayState.h"
#include "Game.h"

/// metodo para simplificar la generacion de objetos y los metodos en los que se generan las entidades de los tableros
///	puesto que se llama muchas veces a estas lineas de manera conjunta,
///	realiza el push back, la asignacion del iterador al objeto y actualiza su rectangulo inicialmente
void Game::addObject(SceneObject*& object)
{ // método para simplificar las inicializaciones del tablero 
	sceneObjs.push_back(object);
	const auto it = --sceneObjs.end();
	object->setIterator(it);
	object->updateRect();
}


/// metodo para vaciar ambas listas de objetos y liberar su memoria, usado previo a cargar partida o mapa
void PlayState::emptyLists()
{
	for (auto it = sceneObjs.begin(); it != sceneObjs.end(); ++it)
	/*
	for (auto i : sceneObjs)
		sceneObjs.erase(i.getIterator());
	for (auto i : deleteObjs)
		deleteObjs.erase(i.getIterator());
	*/
	sceneObjs.clear();
	deleteObjs.clear();
}

/// gestiona las colisiones entre el laser dado y cada objeto en la escena
///	devuelve true si ha colisionado con algo y se invocaran a los metodos
/// correspondientes
bool PlayState::damage(const SDL_Rect*& rect, char friendly)  const 
{
	//std::any_of(sceneObjs.begin(), sceneObjs.end(),);
	for (auto i : sceneObjs)
		if (i.hit(rect, friendly))
			return true;
	return false;
}

/// devuelve un numero aleatorio entre min y max
int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<>(min, max)(randomGenerator);
}