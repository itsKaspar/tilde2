
// ###### Growth Models
// ###### Space Colonization
// ###### Kaspar Ravel - 2020

#include "SCTree.h"

SCTree::SCTree() {
	maxDist = 500;
	minDist = 10;
}

void SCTree::setup() {

	// create random leaves
	for (size_t i = 0; i < 500; i++)
	{
		leaves.push_back(SCLeaf()); // push all leaves back to array of leaves
	}

	ofVec2f rootPosition = ofVec2f(ofGetWidth()/2, ofGetHeight()); // set initial root position
	ofVec2f rootDirection = ofVec2f(0, -1); // set initial root direction                                            // UPDATE THIS TO MAKE IT GO IN THE DIRECTION OF ONE Of THE LEAVES
	SCBranch root = SCBranch(rootPosition, rootDirection); // apply initial root position and direction
	branches.push_back(root); // push root to array of branches
	SCBranch current = SCBranch(&root); // current branch is root

	//cout << root.position << endl;
	//cout << current.position << endl;

	while (!closeEnough(current))
	{
		SCBranch trunk = SCBranch(&current);
		branches.push_back(current);
		current = trunk;
	}

	//for (int i = branches.size() - 1; i >= 0; i--)
	//{
	//	cout << branches[i].position << endl;
	//}

}

bool SCTree::closeEnough(SCBranch b) {
	for (size_t i = 0; i < leaves.size(); i++)
	{
		float d = b.position.distance(leaves[i].position);
		if (d < maxDist) {
			return true;
		}
	}
	return false;
}

void SCTree::grow() {
	//go through every single leaf
	for (size_t i = 0; i < leaves.size(); i++)
	{
		int closest = -1; // &
		ofVec2f closestDir = ofVec2f(0,0);
		float record = 10000000; // record distance so that if we find a close branch, maybe we can see if there is an even close branch
		//int BranchFoundNum = -1;
		//SCBranch closestBranch; // initialized weirdly but actually ok // &

		// find the closest branch to every leaf
		for (size_t j = 0; j < branches.size(); j++)
		{
			ofVec2f dir = leaves[i].position - branches[j].position;
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
			else if ((closest == -1) || ( d < record)) // if a branch hasnt been found
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
	
	for (std::size_t i = leaves.size() - 1; i != -1 ; --i)
	{
		if (leaves[i].reached)
		{
			leaves.erase(leaves.begin() + i); // erase leaf
		}
	}

	for (size_t i = branches.size() - 1; i != -1 ; --i)
	{
		if (branches[i].count > 0)
		{
			branches[i].direction /= (branches[i].count);
			branches[i].direction.normalize();
			SCBranch newB = SCBranch(&branches[i]);
			branches.push_back(newB);
			branches[i].reset();
		}
		
	}
}

void SCTree::drawLeaves() {

	for (size_t i = 0; i < leaves.size(); i++)
	{
		ofSetColor(255, 0, 0, 255);
		ofDrawCircle(leaves[i].position.x, leaves[i].position.y, 3);
		ofSetColor(255, 255, 255, 255);
	}

	for (size_t i = 0; i < branches.size(); i++)
	{
		ofSetColor(0, 255, 0, 255);
		ofDrawCircle(branches[i].position.x, branches[i].position.y, 3);
		ofSetColor(255, 255, 255, 255);
	}
}

SCTree::~SCTree() {
}