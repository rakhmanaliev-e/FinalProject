#include "Processing.h"

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
	SDL_Rect rectangle = { (int)round(x), (int)round(y), 
						(int)round(width), (int)round(height)};
	if (__fillstate == 1) {
		SDL_RenderFillRect(__renderer, &rectangle);
	}
	else {
		SDL_RenderDrawRect(__renderer, &rectangle);
		
	}
}

void Processing::circle(int x, int y, int r) {
	const int diameter = (r * 2);

	int offx = (r - 1);
	int offy = 0;
	int tx = 1;
	int ty = 1;
	int error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(__renderer, x + offx, y - offy);
		SDL_RenderDrawPoint(__renderer, x + offx, y + offy);

		SDL_RenderDrawPoint(__renderer, x - offx, y - offy);
		SDL_RenderDrawPoint(__renderer, x - offx, y + offy);

		SDL_RenderDrawPoint(__renderer, x + offy, y - offx);
		SDL_RenderDrawPoint(__renderer, x + offy, y + offx);

		SDL_RenderDrawPoint(__renderer, x - offy, y - offx);
		SDL_RenderDrawPoint(__renderer, x - offy, y + offx);

		if (error <= 0)
		{
			++offy;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--offx;
			tx += 2;
			error += (tx - diameter);
		}
	}
}
void Processing::line(int startx, int starty, int endx, int endy) {
	SDL_RenderDrawLine(__renderer, startx, starty, endx, endy);
}

void Processing::triangle(int ax, int ay, int bx, int by, int cx, int cy) {
	line(ax, ay, bx, by);
	line(ax, ay, cx, cy);
	line(bx, by, cx, cy);
}
/**
void Processing::text(std::string text, float x, float y) {
	//needs SDL_ttf.h which is not added yet
	//SDL_Surface* surfMessage = TTF



}
*/