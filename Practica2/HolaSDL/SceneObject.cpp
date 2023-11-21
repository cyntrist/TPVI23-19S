#include "SceneObject.h"

void SceneObject::hit(SDL_Rect*& otherRect, char friendly)
{
	if (SDL_HasIntersection(&rect, otherRect)) // faltaría comprobar si es friendly, pero es que depende del objeto?? nose
		lives--; 
}
