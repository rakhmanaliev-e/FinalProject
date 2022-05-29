#include <SDL.h>
#include <iostream>

SDL_Point center{ -45, -45};
int fillstate = 1;

void drawrect(SDL_Renderer* r, int x, int y, int w, int h, double angl) {
	SDL_Texture* tempTexture = SDL_CreateTexture(r, 0, SDL_TEXTUREACCESS_TARGET, w, h);
	SDL_SetRenderTarget(r, tempTexture);


	SDL_Rect rectangle = { 0, 0, (int)round(w), (int)round(h) };

	if (!fillstate) {
		SDL_RenderDrawRect(r, &rectangle);
	}
	else {
		SDL_RenderFillRect(r, &rectangle);
	}
	

	SDL_SetRenderTarget(r, NULL);

	SDL_Rect dest{ x, y, w, h };
	SDL_RenderCopyEx(r, tempTexture, NULL, &dest, angl, &center, SDL_FLIP_NONE);

	SDL_DestroyTexture(tempTexture);

}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	SDL_Window* win = SDL_CreateWindow("field",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		300, 200, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 254, 254, 254, 254);



	int x = 90, y = 90;
	int dx = 3;
	double agl = 0.0;

	SDL_Event e;
	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) { // event for window closing
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0,0,0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 254, 254, 254, 254);

		for (int i = 10; i < 300; i+=10) {
			SDL_RenderDrawLine(renderer, i, 0, i, 300);
			SDL_RenderDrawLine(renderer, 0, i, 300, i);
		}
		std::cout << 
		drawrect(renderer, x, y, 10, 20, agl);
		agl += dx;
		if (x <= 0 || x >= 300 - 10) { dx *= -1; }

		SDL_Delay(100);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
