
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
	std::shared_ptr<RandomWalker> r = std::make_shared<RandomWalker>(glm::vec3(0, 0, 0), walkerRadius, 0, 1, rndColorInterpol); 
	fixed.push_back(r);
	octree->insert(r); // insert first one into octree

	// ##### Walkers Spawn

	for (int i = 0; i < nWalkers; i++) {
		// random color interpol
		float rndColorInterpol = ofRandom(0, 1);
		walkers.push_back(std::make_shared<RandomWalker>(walkerRadius, sWalkers, sticky, rndColorInterpol, is3D));
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
		walkers.push_back(std::make_shared<RandomWalker>(walkerRadius, sWalkers, sticky, rndColorInterpol, is3D));
	}

	// ##### Update Position

	for (std::size_t i = 0; i != walkers.size(); ++i)
	{
		// Calculate the force that draws them towards the aggregation
		int randFixed = (int)ofRandom(0, fixed.size() - 1);
		glm::vec3 aggregation = fixed[randFixed]->pos;
		glm::vec3 towardsAgg = aggregation - walkers[i]->pos;
		walkers[i]->applyVelocity(towardsAgg * (float)(towardsAggregation)/100);

		// Walk && Update
		walkers[i]->update(is3D);
	}

	// ##### Update State

	for (std::size_t i = walkers.size() - 1; i != -1; --i)
	{
		// find which particle is in range 
		vector<std::shared_ptr<Particle>> found = octree->queryInRadius(walkers[i], walkers[i]->radius * 2 + 1);

		for (std::size_t j = found.size() - 1; j != -1; --j) // go through every fixed/dead particles
		{
			// Calculate chance to stick
			bool stick;
			if (sticky > ofRandom(0, 1))
			{stick = true;}
			else {stick = false;}

			// Calculate Distance
			float distance = glm::distance(walkers[i]->pos, found[j]->pos); // calculate the distance between them

			if (distance < (walkers[i]->radius * 2) && stick) // if the distance is small enough
			{
				walkers[i]->randomWalk = 0; // make it dead
				fixed.push_back(walkers[i]); // put it in the fixed/dead vector
				octree->insert(walkers[i]); // insert into octree
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
			walkers[i]->draw(c1, c2, opacity, is3D);
		}
	}

	// ##### Fixed Particles Display

	for (std::size_t i = 0; i != fixed.size(); ++i)
	{
		fixed[i]->draw(c1, c2, opacity, is3D);
	}
}