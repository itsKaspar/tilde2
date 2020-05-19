
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SpaceColonization.h"

SpaceColonization::SpaceColonization() {}

SpaceColonization::~SpaceColonization() {}

ofParameterGroup SpaceColonization::gui() {
	// ##### GUI Setup
	params.setName("Space Colonization");
	params.add(is3D.set("3D", false));
	//params.add(drawOctree.set("Draw Octree", false));
	return params;
}

void SpaceColonization::setup() {
	maxDist = 500;
	minDist = 100;

	// # Creation of Random Leaves
	for (size_t i = 0; i < 500; i++)
	{
		leaves.push_back(SCLeaf());
	}

	// # Initial Root Position
	ofVec3f rootPosition = ofVec3f(0,0,0);

	// # Initial Root Direction
	// get a random leaf and choose it as initial direction
	int r = ofRandom(0, leaves.size()-1);
	ofVec3f rootDirection = leaves[r].position - rootPosition;
	rootDirection.normalize();     

	// # Apply initial root position & direction
	SCBranch root = SCBranch(rootPosition, rootDirection); 

	branches.push_back(root); // push root to array of branches
	SCBranch current = SCBranch(&root); // current branch is root

	while (!closeEnough(current))
	{
		SCBranch trunk = SCBranch(&current);
		branches.push_back(current);
		current = trunk;
	}
}

void SpaceColonization::update() {
	//go through every single leaf
	for (size_t i = 0; i < leaves.size(); i++)
	{
		int closest = -1; // &
		ofVec3f closestDir = ofVec3f(0, 0, 0);
		float record = 10000000; // record distance so that if we find a close branch, maybe we can see if there is an even close branch
		//int BranchFoundNum = -1;
		//SCBranch closestBranch; // initialized weirdly but actually ok // &

		// find the closest branch to every leaf
		for (size_t j = 0; j < branches.size(); j++)
		{
			ofVec3f dir = leaves[i].position - branches[j].position;
			float d = dir.length();
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
			closestDir.normalize();
			branches[closest].direction += closestDir;
			branches[closest].count++;
		}
	}

	for (std::size_t i = leaves.size() - 1; i != -1; --i)
	{
		if (leaves[i].reached)
		{
			leaves.erase(leaves.begin() + i); // erase leaf
		}
	}

	for (size_t i = branches.size() - 1; i != -1; --i)
	{
		if (branches[i].count > 0)
		{
			branches[i].direction /= (branches[i].count);

			// add a tiny bit of random so it can skew towards lost leaves
			ofVec3f rand = ofVec3f(ofRandom(-100,100), ofRandom(-100, 100), ofRandom(-100, 100));

			rand.limit(0.3); // limit magnitude                                                                  // MAKE THIS A PARAMETER from 0 to 1 default .3
			branches[i].direction += rand;

			branches[i].direction.normalize();
			SCBranch newB = SCBranch(&branches[i]);
			branches.push_back(newB);
			branches[i].reset();
		}

	}
}

void SpaceColonization::draw() {

	line.clear();

	for (size_t i = 0; i < leaves.size(); i++)
	{
		ofSetColor(255, 0, 0, 255);
		ofDrawCircle(leaves[i].position.x, leaves[i].position.y, leaves[i].position.z, 3);
	}

	for (size_t i = 0; i < branches.size(); i++)
	{
		ofSetColor(c2, opacity);
		//ofDrawCircle(branches[i].position.x, branches[i].position.y, branches[i].position.z, 3);
		line.addVertex(branches[i].position.x, branches[i].position.y, branches[i].position.z);
	}

	line = line.getResampledBySpacing(15);
	line = line.getSmoothed(50);

	line.draw();

}

void SpaceColonization::reset() {
	leaves.clear();
	branches.clear();
	setup();
}

bool SpaceColonization::closeEnough(SCBranch b) {
	for (size_t i = 0; i < leaves.size(); i++)
	{
		float d = b.position.distance(leaves[i].position);
		if (d < maxDist) {
			return true;
		}
	}
	return false;
}

