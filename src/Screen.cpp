/*
 * Screen.cpp
 *
 *  Created on: 1 Oct 2020
 *      Author: barr
 */

#include "Screen.h"

namespace fartsimulator {

Screen::Screen(): m_window(NULL),m_renderer(NULL),m_texture(NULL),m_buffer1(NULL), m_buffer2(NULL) {

}

bool Screen::init() {

	if(SDL_Init(SDL_INIT_VIDEO) < 0) { // initiating SDL
		return	false;
	}

	m_window = SDL_CreateWindow("Barr's fart simulator", // creating a window
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); //creates a renderer
	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, //creates a texture
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	//creates buffers
	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	//set all buffers' values to 0
	memset(m_buffer1, 0, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_HEIGHT*SCREEN_WIDTH*sizeof(Uint32));

	return true;
}

void Screen::close() {

	delete [] m_buffer1;
	delete [] m_buffer2;
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

bool Screen::processEvents() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return true;
		}
	}
	return false;
}

void Screen::update() {

	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if (x < 0 || x >=SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return;

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::boxBlur() {

	Uint32 *temp = m_buffer2;
	m_buffer2 = m_buffer1;
	m_buffer1 = temp;

	for (int y=0; y < SCREEN_HEIGHT; y++) {
		for (int x=0; x < SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) { // Blur box loop
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH &&
							currentY >=0 && currentY < SCREEN_HEIGHT) {

						Uint32 color = m_buffer2[currentX + currentY*SCREEN_WIDTH]; // RRGGBBAA

						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			} // Blur box ends

			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x, y, red, green, blue);
		}
	}

}

} /* namespace fartsimulator */
