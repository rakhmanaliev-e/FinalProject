#include "Processing.h"
#include <vector>
#include <algorithm>
//void Processing::settings() {}	// to be overridden by user
//void Processing::setup()	{}	//to be overriden by user
//void Processing::draw()		{}	// to be overridden by user

void Processing::run() {
	__window = NULL;
	__renderer = NULL;
	if (__initWithSettings() == -1) {
		return;
	}
	setup(); // user space

	bool quit = false;

	SDL_Event e;

	while (!quit) {

		while (SDL_PollEvent(&e) != 0) { // event for window closing
			if (e.type == SDL_QUIT) {
				quit = true;
			}
		}


		draw(); // user space

		SDL_Delay(__drawupdaterate);
		SDL_RenderPresent(__renderer);

		
	}

	__close();
}

int Processing::__initWithSettings() {
	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;
	try {
		__initSDL();
	}
	catch (std::string err) {
		printf("%s\n", err);
		return -1;
	}
	settings(); // user's code is here
	try {
		__initWindow();
	}
	catch (std::string err) {
		printf("%s \n", err);
		return -1;
	}
	try {
		__initRender();
	}
	catch (std::string err) {
		printf("%s \n", err);
		return -1;
	}
	return 0;
}

void Processing::__close() {
	
	SDL_DestroyRenderer(__renderer);
	SDL_DestroyWindow(__window);
	__renderer = NULL;
	__window = NULL;

	//IMG_Quit();
	SDL_Quit();
}


// private sector
void Processing::__initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw("SDL_Initialization Failed.");
		return;
	}
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled!");
	}
}

void Processing::__initWindow()
{
	char* name = &__winName[0];
	__window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
					SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (__window == NULL)
	{
		throw("Window init fail.");
	}
}

void Processing::__initRender()
{
	__renderer = SDL_CreateRenderer(__window, -1, SDL_RENDERER_ACCELERATED);
	if (__renderer == NULL)
	{
		throw("Render init failed.");
		return;
	}
	SDL_SetRenderDrawColor(__renderer, 0xFF, 0xFF,0xFF,0xFF);
}


// utilities

void Processing::size(int width, int height) {
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}
void Processing::setwait(int waittime) {
	if (waittime > 0)
		__drawupdaterate = waittime;
}

void Processing::background(int col) {
	fill(col);
	SDL_RenderClear(__renderer);
}
void Processing::background(int r, int g, int b) {
	fill(r, g, b);
	SDL_RenderClear(__renderer);
	SDL_RenderPresent(__renderer);
}

void Processing::wait(int amount) {
	SDL_Delay(__drawupdaterate);
}

void Processing::redraw() {
	SDL_RenderPresent(__renderer);
}

void Processing::setName(std::string name) {
	__winName = name;
}
// drawpart

void Processing::fill(float col) {
	int color = (int)col;
	if (color > 255 || color < 0) {
		printf("Fill error: wrong input\n");
	}
	SDL_SetRenderDrawColor(__renderer, (Uint8)col, (Uint8)col, (Uint8)col, 0xFF);
}

void Processing::fill(float r, float g, float b) {
	if (r > 255 || r < 0 || 
		g > 255 || g < 0 || 
		b > 255 || b < 0) 
	{
		printf("Fill error: wrong input\n");
	}
	SDL_SetRenderDrawColor(__renderer, (Uint8)round(r), (Uint8)round(g), (Uint8)round(b), 0xFF);
}

void Processing::rect(float x, float y, float width, float height)
{
	SDL_Texture* tempTexture = SDL_CreateTexture(__renderer, 0, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetRenderTarget(__renderer, tempTexture);


	SDL_Rect rectangle = { 0, 0, 
						(int)round(width), (int)round(height)};
	
	if (__fillstate == 1) {
		SDL_RenderFillRect(__renderer, &rectangle);
	}
	else {
		SDL_RenderDrawRect(__renderer, &rectangle);

	}

	SDL_SetRenderTarget(__renderer, NULL);

	SDL_Rect dest{ x, y, width, height};
	SDL_RenderCopyEx(__renderer, tempTexture, NULL, &dest, __angle, &__centerPoint, SDL_FLIP_NONE);

	SDL_DestroyTexture(tempTexture);

}

void Processing::circle(float x, float y, float r) {
	SDL_Texture* tempTexture = SDL_CreateTexture(__renderer, 0, SDL_TEXTUREACCESS_TARGET, r*2+1, r*2+1);
	SDL_SetRenderTarget(__renderer, tempTexture);

	const float eps{ 0.0000001f };
	float sqrr{ r * r };
	for (int ty = 0; ty <= r; ++ty) {
		float compY{ ty * ty + sqrr - 2 * ty * r };
		for (int tx = 0; tx <= r; ++tx) {
			float compX{ tx * tx - 2 * tx * r };

			float point{compX + compY}; // reduced sqrr from compX already

			if (point < eps) {
				if (!__fillstate) {
					if (point > -eps) { // only the edje
						SDL_RenderDrawPoint(__renderer, x + tx, y + ty);
						SDL_RenderDrawPoint(__renderer, x + tx, y - ty);
						SDL_RenderDrawPoint(__renderer, x - tx, y + ty);
						SDL_RenderDrawPoint(__renderer, x - tx, y - ty);
					}
				}
				else { // inside the circle
					SDL_RenderDrawPoint(__renderer, x + tx, y + ty);
					SDL_RenderDrawPoint(__renderer, x + tx, y - ty);
					SDL_RenderDrawPoint(__renderer, x - tx, y + ty);
					SDL_RenderDrawPoint(__renderer, x - tx, y - ty);
				}
			}
		}
	}
	SDL_SetRenderTarget(__renderer, NULL);
	
	SDL_Rect dest{x - r, y - r, x+r, y+r};
	SDL_RenderCopyEx(__renderer, tempTexture, NULL, &dest , __angle, &__centerPoint, SDL_FLIP_NONE);

	SDL_DestroyTexture(tempTexture);

}

void Processing::line(int startx, int starty, int endx, int endy) {
	SDL_RenderDrawLine(__renderer, startx, starty, endx, endy);
}

void Processing::triangle(float ax, float ay, float bx, float by, float cx, float cy) {
	if (!__fillstate) {
		line(ax, ay, bx, by);
		line(bx, by, cx, cy);
		line(cx, cy, ax, ay);
	
	} else {
		int boundminx = std::min((int)ax, std::min((int)bx, (int)cx));
		int boundmaxx = std::max((int)ax, std::max((int)bx, (int)cx));

		int boundminy = std::min((int)ay, std::min((int)by, (int)cy));
		int boundmaxy = std::max((int)ay, std::max((int)by, (int)cy));

		SDL_Point pts[3] = {{(int)ax - boundminx, (int)ay - boundminy},
							{(int)bx - boundminx, (int)by - boundminy},
							{(int)cx - boundminx, (int)cy - boundminy} };

		std::vector<SDL_Point> edges;
		for (int i = 0; i < 2; ++i) {
			int ind1 = i, ind2 = (i+1) % 3;
			if (pts[ind1].y != pts[ind2].y) {
				if (pts[ind1].y > pts[ind2].y) {
					int t = ind1;
					ind1 = ind2;
					ind2 = t;
				}
				int leny = pts[ind2].y - pts[ind1].y;
				int lenx = pts[ind2].x - pts[ind2].x;

				float k = static_cast<float>(lenx) / leny;

				int cnt = 0;
				for (int ty = pts[ind1].y; ty < pts[ind2].y; ++ty) {
					int tx = static_cast<int>((pts[ind1].x + (k * cnt)));
					edges.push_back({tx, ty});
					cnt++;
				}
			}
		}
		SDL_Texture* tempTexture = SDL_CreateTexture(__renderer, 0, SDL_TEXTUREACCESS_TARGET, boundmaxx - boundminx, boundmaxy - boundminy);
		SDL_SetRenderTarget(__renderer, tempTexture);
	
	
		std::sort(edges.begin(), edges.end(), [](SDL_Point a, SDL_Point b) {return (a.y != b.y ? a.y < b.y : a.x < b.x); });
		for (int i = 0; i < edges.size() - 1; i += 2) {
			int ind1 = i, ind2 = i + 1;
			for (int tx = edges[ind1].x; tx <= edges[ind2].x; ++tx) {
				SDL_RenderDrawPoint(__renderer, tx, edges[i].y);
			}
		}
		SDL_SetRenderTarget(__renderer, NULL);

		SDL_Rect dest{ boundminx, boundminy, boundmaxy - boundminx,  boundmaxy - boundminy };
		SDL_RenderCopyEx(__renderer, tempTexture, NULL, &dest, __angle, &__centerPoint, SDL_FLIP_NONE);

		SDL_DestroyTexture(tempTexture);
	}
}
