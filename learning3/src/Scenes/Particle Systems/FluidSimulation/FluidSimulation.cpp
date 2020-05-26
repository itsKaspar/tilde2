
// ###### Particle Systems
// ###### Fluid Simulation
// ###### Kaspar Ravel - 2020

// ##### Based on Navier-Stokes Equations
// ##### Mike Ash Implementation
// https://mikeash.com/pyblog/fluid-simulation-for-dummies.html

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


}



void FluidSimulation::update() {

}

void FluidSimulation::draw() {
	ofDrawCircle(glm::vec2(0, 0), 2);
}

