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
#include <time.h>
#include <pthread.h>
#include "concrete.h"


float* displacement(float* a, float* b) {
	float* delta = (float*) malloc(3 * sizeof(float));
	delta[0] = b[0] - a[0];
	delta[1] = b[1] - a[1];
	delta[2] = b[2] - a[2];
	return delta;
}

float length(float* a) {
	return sqrt(pow(a[0], 2) + pow(a[0], 2) + pow(a[0], 2));
}

void vector3(float* vec, float x, float y, float z) {
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}


void init_particles(struct particle* particles, int N, float L, float V) {
	for (int i = 0; i < N; i++) {
		particles[i].position[0] = L * ((float)rand() / RAND_MAX);
		particles[i].position[1] = L * ((float)rand() / RAND_MAX);
		particles[i].position[2] = L * ((float)rand() / RAND_MAX);
		particles[i].velocity[0] = V * (((float)rand() / RAND_MAX) - 0.5) * 2;
		particles[i].velocity[1] = V * (((float)rand() / RAND_MAX) - 0.5) * 2;
		particles[i].velocity[2] = V * (((float)rand() / RAND_MAX) - 0.5) * 2;
	}
}

void update_particles(struct particle* particles, float delta, int N) {
	for (int i = 0; i < N; i++) {
		particles[i].velocity[0] += particles[i].acceleration[0] * delta;
		particles[i].velocity[1] += particles[i].acceleration[1] * delta;
		particles[i].velocity[2] += particles[i].acceleration[2] * delta;
		particles[i].position[0] += particles[i].velocity[0] * delta;
		particles[i].position[1] += particles[i].velocity[1] * delta;
		particles[i].position[2] += particles[i].velocity[2] * delta;
	}
}

void bound_particles(struct particle* particles, float L, int N) {
	for (int i = 0; i < N; i++) {
		if (particles[i].position[0] < 0 && particles[i].velocity[0] < 0) { particles[i].velocity[0] *= -1; particles[i].position[0] = 0; }
		if (particles[i].position[0] > L && particles[i].velocity[0] > 0) { particles[i].velocity[0] *= -1; particles[i].position[0] = L; }
		if (particles[i].position[1] < 0 && particles[i].velocity[1] < 0) { particles[i].velocity[1] *= -1; particles[i].position[1] = 0; }
		if (particles[i].position[1] > L && particles[i].velocity[1] > 0) { particles[i].velocity[1] *= -1; particles[i].position[1] = L; }
		if (particles[i].position[2] < 0 && particles[i].velocity[2] < 0) { particles[i].velocity[2] *= -1; particles[i].position[2] = 0; }
		if (particles[i].position[2] > L && particles[i].velocity[2] > 0) { particles[i].velocity[2] *= -1; particles[i].position[2] = L; }
	}
}

void print_particles(struct particle* particles, int N) {
	for (int i = 0; i < N; i++) printf("%f\t%f\t%f\t", particles[i].position[0], particles[i].position[1], particles[i].position[2]);
	printf("\n");
}

void accelerate_particles(struct particle* particles, float M, int N) {
	for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) if (i != j) {
		float* delta = displacement(particles[i].position, particles[j].position);
		float dist = length(delta);
		
		if (dist <= 2 * R) {
			float fn = hertz_mindlin(2 * R - dist) / M;
			
			particles[i].acceleration[0] = -fn * (delta[0] / dist);
			particles[i].acceleration[1] = -fn * (delta[1] / dist);
			particles[i].acceleration[2] = -fn * (delta[2] / dist);
		}
		
		// particles[i].acceleration[2] -= G;
	}
}

float hertz_mindlin(float overlap) {
	float fn = (4/3) * K * R * pow(overlap, 1.5);
	if (fn != fn) printf("Error estimating Hertz-Mindling force!\t%f\n", fn);
	return fn;
}
