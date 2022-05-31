#pragma once

#include <SDL.h>
#include <string>
#include <stdio.h>


class Processing {

private:
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
	int width = 640;
	int height = 480;

	long long frameCount = 0;
	bool _keyPressed = 0;
	bool _mousePressed = 0;
	int pmouseX = 0;
	int pmouseY = 0;
	// find out how to update mouse position real time
	int mouseX = 0;
	int mouseY = 0;

	const char* key = nullptr;
	const char* mouseButton = nullptr;



	// main functions to be overridden by user
	virtual void settings() {};
	virtual void setup() {};
	virtual void draw() {};
	virtual void keyPressed() {};
	virtual void keyReleased() {};
	// new:
	virtual void mouseClicked() {};
	virtual void mouseDragged() {};
	virtual void mouseMoved() {};
	virtual void mousePressed() {};
	virtual void mouseReleased() {};
	virtual void mouseWheel() {};

	// utilities
	void frameRate(float fps);
	int size(int width, int height);
	void fullScreen();
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
	virtual ~Processing() {}
	void run();
	void setName(std::string name);
};

