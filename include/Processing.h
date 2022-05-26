#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_gfx.h>
#include <string>
#include <stdio.h>


class Processing {

private:
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	int __drawupdaterate = 1;

	// camera vector
	int translate[2][2];
	// rotation vector

	std::string __winName;
	int __fillstate = 1;

	SDL_Window* __window;

	SDL_Surface* __surface = NULL;
	SDL_Renderer* __renderer = NULL;

	int	__initWithSettings();
	void __initSDL(); 
	void __initWindow();
	void __initRender();
	
	void __close();
protected:
	class SmartPointer;

	// main functions to be overridden by user
	virtual void settings() = 0;
	virtual void setup() = 0;
	virtual void draw() = 0;

	// utilities
	void size(int width, int height);
	void setwait(int waittime);
	void background(int col);
	void background(int r, int g, int b);
	void wait(int amount);
	void redraw();

	// drawpart
	void fill(float col);
	void fill(float r, float g, float b);
	void rect(float x, float y, float width, float height);
	void circle(int x, int y, int r);
	void line(int startx, int starty, int endx, int endy);
	void triangle(int ax, int ay, int bx, int by, int cx, int cy);
	//void text(std::string text, float x, float y);

public:
	Processing() {}
	virtual ~Processing() { __close(); }
	void run();
	void setName(std::string name);
};



template <class T>
class SmartPtr {
	T* ptr;
public:
	explicit SmartPtr(T* p = NULL) { ptr = p; }

	~SmartPtr() { delete (ptr); }

	T& operator*() { return *ptr; }

	T* operator->() { return ptr; }
};
