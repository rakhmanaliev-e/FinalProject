#pragma once

#include <SDL.h>
#include <string>
#include <stdio.h>


class Processing {

private:
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	Uint32 __drawupdaterate = 1;

	// camera vector
	double __angle{ 0 };
	SDL_Point __centerPoint{ 0,0 };

	std::string __winName;
	int __fillstate = 1;
	int __strokestate = 1;

	SDL_Window* __window;
	SDL_Renderer* __renderer = NULL;


	int	__initWithSettings();
	void __initSDL(); 
	void __initWindow();
	void __initRender();
	
	void __close();
protected:
	long long frameCount = 0;
	bool _keyPressed = 0;
	const char* key = nullptr;
	class SmartPointer;

	// main functions to be overridden by user
	virtual void settings() {};
	virtual void setup() {};
	virtual void draw() {};
	virtual void keyPressed() {};

	// utilities
	void frameRate(float fps);
	void size(int width, int height);
	void background(int col);
	void background(int r, int g, int b);
	void wait(int amount);
	void redraw();

	// drawpart
	void fill(float col);
	void fill(float r, float g, float b);
	void rect(float x, float y, float width, float height);
	void circle(float x, float y, float r);
	void line(int startx, int starty, int endx, int endy);
	void triangle(float ax, float ay, float bx, float by, float cx, float cy);
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
