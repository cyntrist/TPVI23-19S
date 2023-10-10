#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>

using namespace std;

using uint = unsigned int;

void firstTest()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	constexpr uint winWidth = 3840; //resolucion para dos monitores del laboratorio
	constexpr uint winHeight = 1080;
	constexpr uint dogFrameWidth = 128;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	SDL_SetWindowPosition(window, -1920, 0); //para los dos monitores del laboratorio
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		SDL_Texture* texture;
		string filename = "..\\images\\background1.png";
		SDL_Surface* surface = IMG_Load(filename.c_str());
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		//vector<SDL_Texture*> perro;
		SDL_Texture* perro;
		filename = "..\\images\\animate.bmp";
		SDL_Surface* superficie = SDL_LoadBMP(filename.c_str());
		SDL_SetColorKey(superficie, 1, SDL_MapRGB(superficie->format, 0, 0, 0));
		perro = SDL_CreateTextureFromSurface(renderer, superficie);
		SDL_FreeSurface(superficie);

		SDL_Rect originRect;
		originRect.w = 128;
		originRect.h = 82;
		originRect.x = originRect.y = 0;
		
		SDL_Rect destRect;
		destRect.w = 128;
		destRect.h = 82;
		destRect.x = 350;
		destRect.y = 400;

		SDL_FreeSurface(superficie);

		//SDL_SetRenderDrawColor(renderer, 100, 100, 0, 255);
		//SDL_SetTextureColorMod(texture, 100, 100, 0);
		while (true) 
		{
			if (originRect.x < superficie->w - dogFrameWidth)
				originRect.x += dogFrameWidth;
			else
				originRect.x = 0;

			if (destRect.x < signed(winWidth))
				destRect.x += 32;
			else
				destRect.x = - signed(dogFrameWidth);
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderCopy(renderer, perro, &originRect, &destRect);
			SDL_RenderPresent(renderer);
			SDL_Delay(100);
		}
		SDL_DestroyTexture(texture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	firstTest();
	return 0;
}
