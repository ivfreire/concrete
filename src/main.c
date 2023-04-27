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
	
	vector3(particles[0].position, 0.4, 0.5, 0.5);
	vector3(particles[1].position, 0.6, 0.5, 0.5);
	vector3(particles[0].velocity, 1.0, 0.0, 0.0);
	vector3(particles[1].velocity, -1.0, 0.0, 0.0);

	int n = 2;

	// Main loop
	for (int t = 0; t < 1000000; t++) {
		accelerate_particles(particles, M, N);
		bound_particles(particles, L, N);
		update_particles(particles, DELTA, N);
		// if (t % 1000 == 0) print_particles(particles, n);
	}

	free(particles);
	return 0;
}
