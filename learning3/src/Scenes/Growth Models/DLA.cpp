
// ###### Growth Model Studies
// ###### Diffusion Limited Aggregation
// ###### Kaspar Ravel - 2020

#include "DLA.h"

void DLA::setup() {

	// ##### Settings

	spawn = "random";
	walkerQty = 500;
	walkerWalk = 1;
	sticky = 1;

	// ##### Spawn Initial Dead

	fixed.push_back(RandomWalker(ofGetWidth() / 2, ofGetHeight() / 2, 0, 0, 1));

	// ##### Spawn First lot of Walkers

	for (int i = 0; i < walkerQty; i++) {
		walkers.push_back(RandomWalker(spawn, walkerWalk, sticky));
	}
}

void DLA::update() {

	// ##### Feed New Walkers

	while (walkers.size() < walkerQty)
	{
		walkers.push_back(RandomWalker(spawn, walkerWalk, sticky));
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
		for (std::size_t j = fixed.size() - 1; j != -1; --j) // go through every fixed/dead particles
		{
			// Calculate chance to stick
			bool stick;
			if (sticky > ofRandom(0, 1))
			{stick = true;}
			else {stick = false;}

			// Calculate Distance
			float distance = walkers[i].position.distance(fixed[j].position); // calculate the distance between them

			if (distance < (walkers[i].radius + fixed[j].radius) && stick) // if the distance is small enough
			{
				walkers[i].randomWalk = 0; // make it dead
				fixed.push_back(walkers[i]); // put it in the fixed/dead vector
				walkers.erase(walkers.begin() + i); // take it out from the main alive vector
				break;
			}
		}
	}
}

void DLA::draw() {


	if (displayWalkers)
	{
		for (std::size_t i = 0; i != walkers.size(); ++i)
		{
			ofDrawCircle(walkers[i].position.x, walkers[i].position.y, walkers[i].radius);
		}
	}

	for (std::size_t i = 0; i != fixed.size(); ++i)
	{
		ofDrawCircle(fixed[i].position.x, fixed[i].position.y, fixed[i].radius);
	}
}

ofParameterGroup DLA::gui() {

	// ##### GUI Setup
	params.setName("DLA");
	params.add(sticky.set("Stickiness", 0.5, 0.0, 1.0));
	params.add(towardsAggregation.set("Towards Aggregation", 0.0, 0.0, 1));
	params.add(displayWalkers.set("Display Walkers", true));

	return params;
}