
// ###### Particle Systems
// ###### Boids
// ###### Kaspar Ravel - 2020

#include "Boids.h"

ofParameterGroup Boids::gui() {

	// ##### GUI Setup

	params.setName("Boids");
	params.add(scale.set("Scale", 0.1, 0.01, 1)); // make this a type variable
	params.add(rotation.set("Rotation", ofVec3f(0, 1, 0.5), ofVec3f(-1, -1, -1), ofVec3f(1, 1, 1)));
	return params;
}

void Boids::setup() {

	// ##### Boid Spawner

	boidQty = 500;

	for (int i = 0; i < boidQty; i++) {
		// create boid
		// assign random position inside unit sphere
		// assign random image / color / shape
	}
}

void Boids::update() {

}

void Boids::draw() {


}