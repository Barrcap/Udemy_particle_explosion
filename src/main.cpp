//============================================================================
// Name        : SDL.cpp
// Author      : Barr
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <math.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
using namespace std;
using namespace fartsimulator;

int main() {

	const double COLOR_CHANGE_SPEED = 0.001;
	srand(time(NULL));

	Screen screen;
	if (screen.init() == false) {
		cout << "Error initialising SDL" << endl;
	}

	Swarm swarm;
	unsigned char red, green, blue; // RGB represented by a Byte

	while (true) { //game loop


		int elapsed = SDL_GetTicks(); // Getting how many milliseconds passed since started program

		// Update particle
		swarm.update(elapsed);

		// 0<(1+Sin[x])<2, want to get a value between 0 and 255
		red = (unsigned char)((1 + sin(elapsed * 1 * COLOR_CHANGE_SPEED)) * 128);
		green = (unsigned char)((1 + sin(elapsed * 2 * COLOR_CHANGE_SPEED)) * 128);
		blue = (unsigned char)((1 + sin(elapsed * 3 * COLOR_CHANGE_SPEED)) * 128);

		const Particle * const pParticle = swarm.getPerticle();

		// Draw particles
		for (int i=0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticle[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
			int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();

		// Draw the screen
		screen.update();

		// Check for massages/events (quit event)
		if (screen.processEvents())
			break;

	} // Game loop end

	screen.close();

	return 0;
}
