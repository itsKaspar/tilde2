
// ###### Particle Systems
// ###### Fluid Simulation
// ###### Kaspar Ravel - 2020

// ##### Based on Navier-Stokes Equations
// ##### Mike Ash Implementation
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

#pragma once

#ifndef _FLUID
#define _FLUID

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"

#define N 180
#define iter 0

class Fluid
{
public:

	// ##### Basic Functions

	Fluid();
	Fluid(float t, float diffusion, float viscosity);
	~Fluid();

	int IX(int x, int y);
	void fluidStep();

	void addDensity(int x, int y, float amount);
	void addVelocity(int x, int y, float amountX, float amountY);

	void diffuse(int b, float x[], float x0[], float diff, float dt);
	void project(float velocX[], float velocY[], float p[], float div[]);
	void advect(int b, float d[], float d0[], float velocX[], float velocY[], float dt);

	void lin_solve(int b, float x[], float x0[], float a, float c);
	void set_bnd(int b, float x[]);

	void renderD(ofColor c);

	// #### Fluid Dynamics                                


	int size; // 
	float dt; // timestep
	float diff; // diffusion amount
	float visc; // viscosity

	float s[N*N] = { 0 };
	float density[N*N] = { 0 };

	float Vx[N*N] = { 0 };
	float Vy[N*N] = { 0 };

	float Vx0[N*N] = { 0 }; //previous velocity
	float Vy0[N*N] = { 0 };


private:
};

#endif
