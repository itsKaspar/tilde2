
// ###### Growth Model Studies
// ###### Diffusion Limited Aggregation
// ###### Kaspar Ravel - 2020

#include "DLA.h"

ofParameterGroup DLA::gui() {

	// ##### GUI Setup

	params.setName("DLA");
	params.add(xSteps.set("x Steps", 1, 1, 1000));
	params.add(isCentered.set("Centered", true));
	params.add(is3D.set("3D", false));
	params.add(drawOctree.set("Draw Octree", false));
	params.add(sticky.set("Stickiness", 1.0, 0.0, 1.0));
	params.add(towardsAggregation.set("Towards Aggregation", 0.0, 0.0, 0.1));
	params.add(nWalkers.set("Walkers Amount", 100, 0, 10000));
	params.add(sWalkers.set("Walkers Step", 0.1, 0.1, 1));
	params.add(walkerRadius.set("Walkers Radius", 0.5, 0.1, 1));
	params.add(displayWalkers.set("Display Walkers", true));
	params.add(spawnMode.set("Spawn Mode", 3, 1, 3));
	return params;
}

//DLA::DLA() {}
//DLA::~DLA() {}

void DLA::reset() {
	walkers.clear();
	fixed.clear();
	octree->reset();
	setup();
}

void DLA::setup() {

	octree = new Octree(ofVec3f::zero(), ofGetWidth() * 2, true);

	// ##### Spawn Initial Dead
	// random color interpol

	float rndColorInterpol = ofRandom(0, 1);
	fixed.push_back(RandomWalker(glm::vec3(0,0,0), walkerRadius, 0, 1, rndColorInterpol));
	octree->insert(glm::vec3(0, 0, 0)); // insert first one into octree

	// ##### Walker Spawn Mode

	switch (spawnMode)
	{
		case 1: spawn = "random"; break;
		case 2: spawn = "walls"; break;
		case 3: spawn = "sphere"; break;
		default: spawn = "random"; break;
	}

	// ##### Walkers Spawn

	for (int i = 0; i < nWalkers; i++) {
		// random color interpol
		float rndColorInterpol = ofRandom(0, 1);
		walkers.push_back(RandomWalker(spawn, walkerRadius, sWalkers, sticky, rndColorInterpol, is3D));
	}
}

void DLA::update() {

	for (size_t i = 0; i < xSteps; i++) // do this as many times as xSteps
	{

	// ##### Feed New Walkers

	while (walkers.size() < nWalkers)
	{
		// random color interpol
		float rndColorInterpol = ofRandom(0, 1);
		walkers.push_back(RandomWalker(spawn, walkerRadius, sWalkers, sticky, rndColorInterpol, is3D));
	}

	// ##### Update Position

	for (std::size_t i = 0; i != walkers.size(); ++i)
	{
		// Calculate the force that draws them towards the aggregation
		int randFixed = (int)ofRandom(0, fixed.size() - 1);
		ofVec3f aggregation = fixed[randFixed].pos;
		ofVec3f towardsAgg = ofVec3f( 
			aggregation.x - walkers[i].pos.x,
			aggregation.y - walkers[i].pos.y,
			aggregation.z - walkers[i].pos.z
		);
		walkers[i].applyForce(towardsAgg*(towardsAggregation)/100);

		// Walk && Update
		walkers[i].update();
	}

	// ##### Update State

	for (std::size_t i = walkers.size() - 1; i != -1; --i)
	{
		// find which particle is in range 
		vector<glm::vec3> found = octree->queryInRadius(walkers[i].pos, walkers[i].radius * 2 + 1);

		for (std::size_t j = found.size() - 1; j != -1; --j) // go through every fixed/dead particles
		{
			// Calculate chance to stick
			bool stick;
			if (sticky > ofRandom(0, 1))
			{stick = true;}
			else {stick = false;}

			// Calculate Distance
			float distance = glm::distance(walkers[i].pos, found[j]); // calculate the distance between them

			if (distance < (walkers[i].radius * 2) && stick) // if the distance is small enough
			{
				walkers[i].randomWalk = 0; // make it dead
				fixed.push_back(walkers[i]); // put it in the fixed/dead vector
				octree->insert(walkers[i].pos); // insert into octree
				walkers.erase(walkers.begin() + i); // take it out from the main alive vector

				break;
			}
		}
	}
	}
}

void DLA::draw() {

	if(drawOctree) octree->draw(c1, c2);

	// ##### Walkers Display

	if (displayWalkers)
	{
		for (std::size_t i = 0; i != walkers.size(); ++i)
		{
			ofColor walkerColor = ofColor(ofColor(c1.r,c1.g,c1.b).lerp(ofColor(c2.r, c2.g, c2.b), walkers[i].ci),opacity);
			//ofSetColor(c1.lerp(c2,walkers[i].ci), opacity);                                                               // CAN USE THIS INSTEAD ?

			if (is3D) // 3D Render
			{
				material.setDiffuseColor(walkerColor);
				material.begin();
				ofDrawSphere(walkers[i].pos.x, walkers[i].pos.y, walkers[i].pos.z, walkers[i].radius); 
			}
			else // 2D Render
			{
				ofSetColor(walkerColor);       
				ofDrawCircle(walkers[i].pos.x, walkers[i].pos.y, walkers[i].radius);
			}
		}
	}

	// ##### Fixed Particles Display

	for (std::size_t i = 0; i != fixed.size(); ++i)
	{
		ofColor fixedColor = ofColor(ofColor(c1.r, c1.g, c1.b).lerp(ofColor(c2.r, c2.g, c2.b), fixed[i].ci), opacity);

		if (is3D) // 3D Render
		{
			material.setDiffuseColor(fixedColor);
			material.begin();
			ofDrawSphere(fixed[i].pos.x, fixed[i].pos.y, fixed[i].pos.z, fixed[i].radius);
		}
		else // 2D Render
		{
			ofSetColor(fixedColor);
			ofDrawCircle(fixed[i].pos.x, fixed[i].pos.y, fixed[i].radius);
		}
	}
}