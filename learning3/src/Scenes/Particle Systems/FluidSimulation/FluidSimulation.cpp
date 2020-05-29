
// ###### Particle Systems
// ###### Fluid Simulation
// ###### Kaspar Ravel - 2020

// ##### Based on Navier-Stokes Equations
// ##### Mike Ash Implementation
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

#include "ofMain.h" 
#include "FluidSimulation.h"

void FluidSimulation::reset() {

}

ofParameterGroup FluidSimulation::gui() {

	// ##### GUI Setup

	params.setName("Fluid Simulation");
	//params.add(scale.set("Scale", 0.1, 0.01, 1)); // make this a type variable
	//params.add(rotation.set("Rotation", ofVec3f(0, 1, 0.5), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
	return params;
}

void FluidSimulation::setup() {
	ofAddListener(ofEvents().mouseMoved, this, &FluidSimulation::mouseMoved);
	fluid = new Fluid(0.1, 0, 0);
}



void FluidSimulation::update() {
	fluid->fluidStep();
}

float mapping(float value, float start1, float stop1, float start2, float stop2)
{
	return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
}

void FluidSimulation::mouseMoved(ofMouseEventArgs & mouse) {

	std::cout << "x = " << (int)ofGetMouseX() << " and Y = " << (int)ofGetMouseY() << endl;

	int x = mapping(ofGetMouseX(), 1, ofGetWidth(), 0, N);
	int y = mapping(ofGetMouseY(), 1, ofGetHeight(), N, 0);

	fluid->addDensity(x, y, 200);

	fluid->addVelocity(x, y, ofRandom(-10,10), ofRandom(-10, 10));

	//std::cout << "new density at : " << (int)ofGetMouseX() / N << " , " << (int)ofGetMouseY() / N << endl;
}

void FluidSimulation::draw() {
	fluid->renderD(c1);
}



