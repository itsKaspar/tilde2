
// ###### Particle Systems
// ###### Boids
// ###### Kaspar Ravel - 2020

#include "Boids.h"

void Boids::reset() {
	boids.clear();
	octree->reset();
	setup();
}

ofParameterGroup Boids::gui() {

	// ##### GUI Setup

	params.setName("Boids");
	params.add(nBoids.set("Boids Qty", 500, 0, 1000));
	params.add(is3D.set("3D", false));
	params.add(drawOctree.set("Draw Octree", false));
	return params;
}

void Boids::setup() {

	octree = new Octree(ofVec3f(0, 0, 0), ofGetWidth() * 2, true);

	// ##### Boid Spawner

	for (int i = 0; i < nBoids; i++) {

		float x = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		float y = is3D ? ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2) : ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
		float z = is3D ? ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2) : 0;
		
		ofVec3f boidPos = ofVec3f(x, y, z);

		boids.push_back(Boid(boidPos));
		octree->insert(boidPos); // insert into octree
	}
}

void Boids::update() {

	for (size_t i = 0; i < boids.size(); i++)
	{
		vector <Boid> neighbours;
		for (size_t j = 0; j < boids.size(); j++)
		{
			float distance = boids[i].pos.distance(boids[j].pos);
			if (distance < 50)
			{
				neighbours.push_back(boids[j]);
			}
		}

		boids[i].alignment(neighbours);
		boids[i].cohesion(neighbours);
		boids[i].separation(neighbours);

		neighbours.clear();
	}

	for (size_t i = 0; i < boids.size(); i++)
	{
		boids[i].update();
		boids[i].edges();
	}

}

void Boids::draw() {

	for (size_t i = 0; i < boids.size(); i++)
	{
		ofDrawCircle(boids[i].pos, 5);                // Make a function to show
	}
}