
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SpaceColonization.h"

SpaceColonization::SpaceColonization() {}

SpaceColonization::~SpaceColonization() {
}

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
		float rX = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		float rY = ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
		float rZ = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);

		if (is3D) leaves.push_back(SCLeaf(ofVec3f(rX, rY, rZ)));
		else leaves.push_back(SCLeaf(ofVec3f(rX, rY, 0)));
	}

	// # Initial Root Position

	ofVec3f rootPosition = ofVec3f(0, 0, 0);
	ofVec3f rootDirection = ofVec3f(0, 0, 0);

	if (!isCentered)
	{
		float rX = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		float rY = ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
		float rZ = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		
		if (is3D) rootPosition = ofVec3f(rX, rY, rZ);
		else rootPosition = ofVec3f(rX, rY, 0);
	}

	// # Initial Root Direction
	// get a random leaf and choose it as initial direction

	int r = ofRandom(0, leaves.size()-1);
	rootDirection = leaves[r].position -rootPosition;
	rootDirection.normalize();     

	// # Apply initial root position & direction

	SCBranch root = SCBranch(rootPosition, rootDirection); 

	branches.push_back(root); // push root to array of branches
	SCBranch current = SCBranch(rootPosition, rootDirection, true); // current branch is root

	while (!closeEnough(current)) // if there are no leaves under the max distance
	{
		//std::cout << "value: " << current.parent->position << endl;
		SCBranch trunk = SCBranch(current.position, current.direction, true);
		branches.push_back(trunk);
		current = trunk;
	}
}


void SpaceColonization::update() {
	
	//go through every single leaf
	for (size_t i = 0; i < leaves.size(); i++)
	{
		int closest = -1; // &
		ofVec3f closestDir;
		float record = -1; // record distance so that if we find a close branch, maybe we can see if there is an even close branch
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

	for (size_t i = branches.size() - 1; i != -1; --i)
	{
		if (branches[i].count > 0)
		{
			branches[i].direction /= (branches[i].count);

			// add a tiny bit of random so it can skew towards lost leaves
			ofVec3f rand = ofVec3f(ofRandom(-100,100), ofRandom(-100, 100), ofRandom(-100, 100));

			rand.limit(crispy); // limit magnitude with crispiness factor
			branches[i].direction += rand;

			branches[i].direction.normalize();
			SCBranch newB = SCBranch(branches[i].position, branches[i].direction, true);
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
			if (leaves[i].reached)
			{
				ofSetColor(c1, opacity);
				ofDrawSphere(leaves[i].position.x, leaves[i].position.y, leaves[i].position.z, 3);
			}
		}
	}

	for (size_t i = 0; i < branches.size(); i++)
	{
		ofSetColor(c2, opacity);

		// Random Connections
		//line.addVertex(branches[i].position.x, branches[i].position.y, branches[i].position.z);

		// Normal Lines

		if (branches[i].hasParent == true)
		{
			float initX = branches[i].position.x;
			float initY = branches[i].position.y;
			float initZ = branches[i].position.z;
			float parentX = branches[i].parentposition.x;
			float parentY = branches[i].parentposition.y;
			float parentZ = branches[i].parentposition.z;
			ofDrawLine(initX, initY, initZ, parentX, parentY, parentZ);
		}
	}

	line = line.getResampledBySpacing(15);
	line = line.getSmoothed(50);
	line.draw();
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

