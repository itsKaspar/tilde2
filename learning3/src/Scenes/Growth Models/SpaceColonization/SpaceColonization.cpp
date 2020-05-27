
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SpaceColonization.h"

//SpaceColonization::SpaceColonization() {}

//SpaceColonization::~SpaceColonization() {}

void SpaceColonization::reset() {
	leaves.clear();
	branches.clear();
	line.clear();
	setup();
}

ofParameterGroup SpaceColonization::gui() {

	// ##### GUI Setup

	params.setName("Space Colonization");
	params.add(isCentered.set("Centered", true));
	params.add(is3D.set("3D", false));
	params.add(drawLeaves.set("Draw Leaves", false));
	params.add(minDist.set("min leaf dist", 5.0, 1.00, 50.0));
	params.add(maxDist.set("max leaf dist", 200.0, 20.0, 1000.0));
	params.add(nLeaves.set("number of leaves", 200.0, 1.0, 5000.0));
	params.add(crispy.set("crispy", 0.0, 0.0, 1.0));
	//params.add(drawOctree.set("Draw Octree", false));                      // RANDOM MOVEMENT  // NUMBER OF LEAVES

	return params;
}

void SpaceColonization::setup() {

	// # Creation of Random Leaves

	for (size_t i = 0; i < nLeaves; i++)
	{	
		leaves.push_back(SCLeaf(is3D));
	}

	// # Initial Root Position

	glm::vec3 rootPos(0, 0, 0);
	glm::vec3 rootDir(0, 0, 0);

	if (!isCentered)
	{
		float rX = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		float rY = ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
		float rZ = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		
		if (is3D) rootPos = glm::vec3(rX, rY, rZ);
		else rootPos = glm::vec3(rX, rY, 0);
	}

	// # Initial Root Direction
	// get a random leaf and choose it as initial direction

	int r = ofRandom(0, leaves.size()-1);
	rootDir = leaves[r].pos - rootPos;
	rootDir = glm::normalize(rootDir);

	// # Apply initial root position & direction

	SCBranch root = SCBranch(rootPos, rootDir); 

	branches.push_back(root); // push root to array of branches
	SCBranch current = SCBranch(rootPos, rootDir, true); // current branch is root

	while (!closeEnough(current)) // if there are no leaves under the max distance
	{
		//std::cout << "value: " << current.parent->position << endl;
		SCBranch trunk = SCBranch(current.pos, current.dir, true);
		branches.push_back(trunk);
		current = trunk;
		std::cout << "value: " << trunk.pos << endl;
	}
}


void SpaceColonization::update() {
	
	//go through every single leaf
	for (size_t i = 0; i < leaves.size(); i++)
	{
		int closest = -1; // &
		glm::vec3 closestDir;
		float record = -1; // record distance so that if we find a close branch, maybe we can see if there is an even close branch

		// find the closest branch to every leaf
		for (size_t j = 0; j < branches.size(); j++)
		{
			glm::vec3 dir = leaves[i].pos - branches[j].pos;
			float d = glm::length(dir);
			if (d < minDist)
			{
				// mark that leaf for deletion
				leaves[i].reached = true;
				closest = -1;
				break;
			}
			else if (d > maxDist)
			{
			}
			else if ((closest == -1) || (d < record)) // if a branch hasnt been found
			{
				closest = j; // get index of closest branch
				closestDir = dir;
				record = d;
			}
		}

		//now for every leaf still, what do we do if closest branch isnt null ? (has been found )
		if (closest != -1)
		{
			closestDir = glm::normalize(closestDir);
			branches[closest].dir += closestDir;
			branches[closest].count++;
		}
	}

	for (size_t i = branches.size() - 1; i != -1; --i)
	{
		if (branches[i].count > 0)
		{
			branches[i].dir /= (branches[i].count);

			// add a tiny bit of random so it can skew towards lost leaves
			//glm::vec3 rand(ofRandom(-100,100), ofRandom(-100, 100), ofRandom(-100, 100));
			//rand = glm::normalize(rand) * (float)crispy; // limit magnitude with crispiness factor
			//branches[i].dir += rand;

			branches[i].dir = glm::normalize(branches[i].dir);
			SCBranch newB = SCBranch(branches[i].pos, branches[i].dir, true);
			branches.push_back(newB);
			branches[i].reset();
		}

	}
	
}

void SpaceColonization::draw() {
	
	line.clear();

	if (drawLeaves)
	{
		for (size_t i = 0; i < leaves.size(); i++)
		{
			leaves[i].draw(c1, opacity);
		}
	}

	for (size_t i = 0; i < branches.size(); i++)
	{
		branches[i].draw(c2, opacity);
		ofSetColor(c2, opacity);



		// Normal Lines

	}

	line = line.getResampledBySpacing(15);
	line = line.getSmoothed(50);
	line.draw();
}



bool SpaceColonization::closeEnough(SCBranch b) {

	for (size_t i = 0; i < leaves.size(); i++)
	{
		float d = glm::distance(b.pos, leaves[i].pos);
		if (d < maxDist) {
			return true;
		}
	}
	return false;

	
}

