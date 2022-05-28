#include "Processing.h"
#include <stdio.h>
#include <string>

// Hanoy showcase

class Canvas : public Processing {
	int x = 100, y = 200;
	int w = 70, h = 30;
	int dx = 4;

	void settings()  override {
		size(600, 500);
	}

	void setup() override {
		fill(100, 100, 100);
	}
	void draw() override {
		background(0);
		circle(x, y, w);
		if (x <= 0 || x >= 600 - w) {
			dx *= -1;
		}
		x += dx;
	}

public:
	Canvas() {}
};


int main(int argc, char* argv[])
{
	Canvas proj;
	proj.setName("Running block");
	proj.run();
	// Canvas::start
	return 0;
}
