#include "Processing.h"
#include <stdio.h>
#include <string>

// Hanoy showcase

class Canvas : public Processing {

	struct disc {
		int there;
		int x, y;
		int width, height;
	};
	void backobjs() {
		fill(0.0, 0.0, 255.0);
		rect(97, 70, 6, 100);
		rect(197, 70, 6, 100);
		rect(297, 70, 6, 100);
	}
	

	void drawdisks() {
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (tow[i][j].there) {
					disc temp = tow[i][j];
					rect((i+1) * 100 - temp.width / 2.0f, temp.y - j * (10 + 5), temp.width, temp.height);
				}
			}
		}
	}

	disc *tow[3];
	

	void settings()  override {
		size(600, 500);
		
	}

	void setup() override {
		setwait(300);
		for (int i = 0; i < 3; ++i) {
			tow[i] = new disc[5];
			for (int j = 0; j < 5; ++j) {
				tow[i][j] = { (i == 0), 100, 150, 10 * (5 - j), 10 };
			}
		}
		

		background(0);
		backobjs();
		hanoy(5, 0, 1, 2);

		
	}

	void liftup(disc d, int ind, int t) {
		for (int y = d.y - ind * (10 + 5); y > 50; y -= 5) {
			background(0);
			backobjs();
			drawdisks();
			rect(t * 100 - (d.width / 2.0f) + 100, y, d.width, d.height);
			wait(0);
			redraw();
		}
	}

	void fly(disc d, int from, int to) {
		for (int x = (from+1) * 100; x != (to+1) * 100; x += (to - from) * 5) {
			background(0);
			backobjs();
			drawdisks();
			rect(x, 50, d.width, d.height);
			wait(0);
			redraw();
		}
	}

	void putdown(disc d, int ind, int t) {
		for (int y = 50; y < d.y - ind * (10 + 5); y += 5) {
			background(0);
			backobjs();
			drawdisks();
			rect(t * 100 - (d.width / 2.0f) + 100, y, d.width, d.height);
			wait(0);
			redraw();
		}
	}



	void move(int from, int to) {
		int ind_from, ind_to = 0;

		for (int i = 4; i >= 0; --i) {
			if (tow[from][i].there) {
				ind_from = i;
				break;
			}
		}
		for (int i = 4; i >= 0; --i) {
			if (tow[to][i].there) {
				ind_to = i + 1;
				break;
			}
		}

		disc moved = tow[from][ind_from];

		tow[from][ind_from].there = 0;

		liftup(moved, ind_from, from);
		fly(moved, from, to);
		putdown(moved, ind_to, to);

		tow[to][ind_to] = moved;
		redraw();
	}


	void hanoy(int n, int t1, int t2, int t3) {
		if (n > 0) {
			hanoy(n - 1, t1, t3, t2);
			move(t1, t2);
			hanoy(n - 1, t3, t2, t1);
			wait(100);
		}
	}
	

	void draw() override {}

public:
	Canvas() {}
};


int main(int argc, char* argv[])
{
	Canvas proj;
	proj.setName("TestCase");
	proj.run();
	// Canvas::start
	return 0;
}
