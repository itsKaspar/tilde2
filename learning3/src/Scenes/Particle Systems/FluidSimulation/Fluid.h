
// ###### Particle Systems
// ###### Fluid Simulation
// ###### Kaspar Ravel - 2020

// ##### Based on Navier-Stokes Equations
// ##### Mike Ash Implementation
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

	/*

#pragma once

#ifndef _FLUID
#define _FLUID

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"


class FluidSimulation : public Scene
{
public:

	// ##### Basic Functions

	FluidSimulation();
	FluidSimulation(float t, float diffusion, float viscosity);
	~FluidSimulation();


	// #### Fluid Dynamics

	int size; // 
	float dt; // timestep
	float diff; // diffusion amount
	float visc; // viscosity

	float *s; 
	float *density;

	float *Vx;
	float *Vy;

	float *Vx0; //previous velocity
	float *Vy0;


private:
};

#endif

	*/