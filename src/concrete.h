/*
	==================================================
	Created on April 26th, 2023.
	Author: Icaro Freire (https://github.com/ivfreire)
	Nuclear & Energy Research Institute - IPEN
	Sao Paulo, Brazil
	==================================================
*/

#ifndef _CONCRETE_H
#define _CONCRETE_H

#define DELTA	1E-6
#define SPEED	1

#define R	200E-6		// m²
#define G	9.81		// m/s²
#define PHO	2600		// kg/m³
#define K	1E5			// ?

// Particle's parameters
struct particle {
	float position[3];
	float velocity[3];
	float acceleration[3];
};

// Box's parameters
struct box {
	float acceleration[3];
	float velocity[3];
	float angular[3];

	float L;
	float H;
	int N;
	int n;
};


// Maths utils
float* displacement(float* a, float* b);
float length(float* a);
void vector3(float* vec, float x, float y, float z);

// Particles functions
void init_particles(struct particle* particles, int N, float L, float V);
void update_particles(struct particle* particles, float delta, int N);
void bound_particles(struct particle* particles, float L, int N);
void print_particles(struct particle* particles, int N);
void accelerate_particles(struct particle* particles, float M, int N);

// Model function
float hertz_mindlin(float overlap);

#endif
