
// ###### Particle Systems
// ###### Fluid Simulation
// ###### Kaspar Ravel - 2020

// ##### Based on Navier-Stokes Equations
// ##### Mike Ash Implementation
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

#pragma once

#ifndef _FLUIDSIMULATION
#define _FLUIDSIMULATION

#include "ofMain.h" 
#include "ofxGui.h"
#include "Scene.h"
#include "Fluid.h"


class FluidSimulation : public Scene
{
public:

	void mouseMoved(ofMouseEventArgs & mouse);

	// ##### Basic Functions

	void setup();
	void update();
	void draw();
	void reset();

	// ##### GUI Setup

	ofParameterGroup gui();
	ofParameterGroup params;

	// ##### Layer Settings

	void setColor1(ofColor color1) { c1 = color1; }
	void setColor2(ofColor color2) { c2 = color2; }
	void setOpacity(int o) { opacity = o; }

	ofColor c1;
	ofColor c2;
	int opacity;

	// ##### General Fluid Setting

	Fluid *fluid;

private:
};

#endif