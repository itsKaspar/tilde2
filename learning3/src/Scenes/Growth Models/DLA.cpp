
// ###### Growth Model Studies
// ###### Diffusion Limited Aggregation
// ###### Kaspar Ravel - 2020

#include "DLA.h"

ofParameterGroup DLA::gui() {

	// ##### GUI Setup

	params.setName("DLA");
	params.add(sticky.set("Stickiness", 0.5, 0.0, 1.0));
	params.add(towardsAggregation.set("Towards Aggregation", 0.0, 0.0, 1));
	params.add(displayWalkers.set("Display Walkers", true));
	return params;
}

DLA::DLA() {
	octree = new Octree(ofVec3f::zero(), ofGetWidth()*2, true);
}
DLA::~DLA() {
	delete this;
}

void DLA::setup() {

	// ##### Settings

	spawn = "random";
	walkerQty = 500;
	walkerWalk = 2;
	sticky = 1;

	// ##### Spawn Initial Dead
	// random color interpol
	float rndColorInterpol = ofRandom(0, 1);
	fixed.push_back(RandomWalker(0, 0, 0, 0, 1, rndColorInterpol));
	octree->insert(ofVec2f(0, 0)); // insert first one into octree

	// ##### Spawn First lot of Walkers

	for (int i = 0; i < walkerQty; i++) {
		// random color interpol
		float rndColorInterpol = ofRandom(0, 1);
		walkers.push_back(RandomWalker(spawn, walkerWalk, sticky, rndColorInterpol));
	}
}

void DLA::update() {

	// ##### Feed New Walkers

	while (walkers.size() < walkerQty)
	{
		// random color interpol
		float rndColorInterpol = ofRandom(0, 1);
		walkers.push_back(RandomWalker(spawn, walkerWalk, sticky, rndColorInterpol));
	}

	// ##### Update Position

	for (std::size_t i = 0; i != walkers.size(); ++i)
	{
		// Calculate the force that draws them towards the aggregation
		int randFixed = (int)ofRandom(0, fixed.size() - 1);
		ofVec3f aggregation = fixed[randFixed].position;
		ofVec3f towardsAgg = ofVec3f( 
			aggregation.x - walkers[i].position.x,
			aggregation.y - walkers[i].position.y,
			aggregation.z - walkers[i].position.z
		);
		walkers[i].applyForce(towardsAgg*(towardsAggregation)/100);

		// Walk && Update
		walkers[i].update();
	}

	// ##### Update State

	for (std::size_t i = walkers.size() - 1; i != -1; --i)
	{
		// find which particle is in range 
		vector<ofVec3f> found = octree->queryInRadius(walkers[i].position, walkers[i].radius * 2 + 1);

		for (std::size_t j = found.size() - 1; j != -1; --j) // go through every fixed/dead particles
		{
			// Calculate chance to stick
			bool stick;
			if (sticky > ofRandom(0, 1))
			{stick = true;}
			else {stick = false;}

			// Calculate Distance
			float distance = walkers[i].position.distance(found[j]); // calculate the distance between them

			if (distance < (walkers[i].radius * 2) && stick) // if the distance is small enough
			{
				walkers[i].randomWalk = 0; // make it dead
				fixed.push_back(walkers[i]); // put it in the fixed/dead vector
				octree->insert(walkers[i].position); // insert into octree
				walkers.erase(walkers.begin() + i); // take it out from the main alive vector

				break;
			}
		}
	}
}

void DLA::draw() {

	octree->draw(c1, c2);

	if (displayWalkers)
	{
		for (std::size_t i = 0; i != walkers.size(); ++i)
		{
			ofSetColor(ofColor(c1.r,c1.g,c1.b).lerp(ofColor(c2.r, c2.g, c2.b), walkers[i].ci),opacity);
			//ofSetColor(c1.lerp(c2,walkers[i].ci), opacity);
			ofDrawCircle(walkers[i].position.x, walkers[i].position.y, walkers[i].radius);
		}
	}

	for (std::size_t i = 0; i != fixed.size(); ++i)
	{
		ofSetColor(ofColor(c1.r, c1.g, c1.b).lerp(ofColor(c2.r, c2.g, c2.b), fixed[i].ci),opacity);
		ofDrawCircle(fixed[i].position.x, fixed[i].position.y, fixed[i].radius);
	}
}