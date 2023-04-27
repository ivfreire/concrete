/*
	==================================================
	Created on April 26th, 2023.
	Author: Icaro Freire (https://github.com/ivfreire)
	Nuclear & Energy Research Institute - IPEN
	Sao Paulo, Brazil
	==================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "concrete.h"

int main(int argc, char* argv[]) {

	float 	L	= 1;
	int 	N	= 2;
	double 	M 	= (4/3) * M_PI * pow(R, 3) * PHO;
	
	// Instanciate particles
	struct particle* particles;
	particles = (struct particle*) malloc(N * sizeof(struct particle));
	
	if (particles == NULL) {
		printf("Could not allocate memory for particles simulation!");
		return -1;
	}

	init_particles(particles, N, L, 1);
	
	vector3(particles[0].position,  0.2, 0.5, 0.5);
	vector3(particles[1].position,  0.8, 0.5, 0.5);
	vector3(particles[0].velocity,  100, 0, 0);
	vector3(particles[1].velocity, -100, 0, 0);

	SDL_Init(SDL_INIT_VIDEO);

	int width = 600;
	int height = 600;

	SDL_Window* window;
	SDL_Renderer* renderer;
	
	window = SDL_CreateWindow(
		"Concrete",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (window == NULL) {
		printf("Could not instanciate window.");
		return -1;
	}

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

	if (renderer == NULL) {
		printf("Could not instanciate renderer.");
		return -1;
	}

	int n = N;

	int ticks = 0;
	float delta = 0.0f;

	int running = 0;
	
	while (running == 0) {

		// Catch events
		SDL_Event ev;
		SDL_PollEvent(&ev);

		if (ev.type == SDL_QUIT) running = 1;

		// Updating
		accelerate_particles(particles, M, N);
		bound_particles(particles, L, N);
		update_particles(particles, DELTA, N);

		// Rendering
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		for (int i = 0; i < n; i++) {
			SDL_Rect rect = {
				(int)(particles[i].position[0] * width),
				(int)(particles[i].position[1] * height),
				10, 10
			};
			SDL_SetRenderDrawColor(renderer, 100*i, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);

		// Calculate FPS
		int dticks = SDL_GetTicks();
		delta = (float)dticks / 1000.0f;
		ticks += dticks;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	free(particles);
	return 0;
}
