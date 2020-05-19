
// ###### Growth Model Studies
// ###### Differential Line Growth 
// ###### Kaspar Ravel - 2020

#include "DiffLine.h"

DiffLine::DiffLine()
{
	octree = new Octree(ofVec3f(0, 0, 0), ofGetWidth() * 2, true);
}
DiffLine::~DiffLine()
{
	nodes.clear();
	delete octree;
}

ofParameterGroup DiffLine::gui() {
	params.add(isCentered.set("Centered", true));
	params.add(is3D.set("3D", false));
	params.add(drawOctree.set("Draw Octree", false));
	return params;
}

void DiffLine::setup() {

	// ##### Initial circle

	float cx = 0;
	float cy = 0;
	float cz = 0;

	if (!isCentered) // Random Positioning
	{
		cx = ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2);
		cy = ofRandom(-ofGetHeight() / 2, ofGetHeight() / 2);
		cz = is3D ? ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2) : 0;
	}

	float i = 0;
	while (i < TWO_PI) { 
		float r = 10;
		float x = cos(i) * r + cx;
		float y = sin(i) * r + cy;
		float z = is3D ? ofRandom(-2, 2) + cz : cz;

		addNode(Node(x, y, z)); // add Node to nodes list

		i += HALF_PI*0.9;
	}
}

void DiffLine::update() {
	grow();
	differentiate();

	// reset and refill octree
	octree->reset(); // reset the octree every frame bc the positions changed
	// NEED TO MAKE A FUNCTION TO UPDATE THE OCTREE INSTEAD OF REPLACING IT, JUST CHECHKING VECTOR POSITIONS
	for (size_t i = 0; i < nodes.size(); i++)
	{
		octree->insert(ofVec3f(nodes[i].position.x, nodes[i].position.y, nodes[i].position.z)); // insert into octree
	}
}

void DiffLine::draw() {

	if (drawOctree) 
	{
		octree->draw(c1, c2);
	}

	line.clear();

	std::vector<Node>::iterator it; // define a list iterator
	for(it = nodes.begin(); it != nodes.end(); it++)
	{
		line.addVertex(it->position.x, it->position.y, it->position.z);
		//it->debugDraw();
	} 

	// if closed shape close using first point
	line.addVertex(nodes[0].position.x, nodes[0].position.y, nodes[0].position.z);
	line.addVertex(nodes[1].position.x, nodes[1].position.y, nodes[1].position.z); // need to add this bc of smoothing makes me loose a point

	line = line.getResampledBySpacing(3);
	line = line.getSmoothed(5);

	line.draw();
}

void DiffLine::reset() {
	nodes.clear();
	setup();
}

void DiffLine::grow() {


	int k = 0;

	// EdgeBreak Growth
	for (std::size_t i = nodes.size(); i != 0; --i)
	{
		ofVec3f v1 = nodes[i % nodes.size()].position;
		ofVec3f v2 = nodes[i - 1].position;

		float distance = v1.distance(v2);
		if (distance > nodes[i - 1].maxEdgeLen) {
			interpolate(i, v1, v2);
		}
	}

	// Random Growth
	/*
	if (rand() % 50 == 0)
	{
		int r = rand() % nodes.size(); // generates random int between 0 and list size
		Node n1 = nodes[idxFix(r + 0)];
		Node n2 = nodes[idxFix(r + 1)];
		interpolate(r, n1.position, n2.position);
	}*/
}

void DiffLine::interpolate(int i, ofVec3f v1, ofVec3f v2) {
	Node n = Node(0, 0, 0);
	n.position = v1.getInterpolated(v2, 0.5);
	addNodeAt(i, n);
}

void DiffLine::differentiate() {


	std::vector<Node>::iterator i; // define a list iterator
	for (std::size_t i = 0; i != nodes.size(); ++i)
	{
		ofVec3f v1 = nodes[i].position;
		ofVec3f v2 = nodes[(i + 1) % nodes.size()].position;

		// Construct Neighbours
		//vector<ofVec3f> neighbours;
		std::vector<Node>::iterator j;

		// Look for nodes in range inside octree
		vector<ofVec3f> found = octree->queryInRadius(nodes[i].position,50);

		/*
		for (std::size_t j = 0; j != nodes.size(); ++j)
		{
			float distance = nodes[i].position.distance(nodes[j].position);
			if (distance < 50) {
				neighbours.push_back(nodes[j].position);
			}
		}*/

		// Get Forces
		ofVec3f attractionForce = nodes[i].attractionForce(v1, v2);
		ofVec3f repulsionForce = nodes[i].repulsionForce(found);

		// Apply Multipliers
		attractionForce = attractionForce * xAttraction;
		repulsionForce = repulsionForce * xRepulsion;

		// Apply Forces in the Velocity cache
		nodes[i].applyForce(attractionForce * 1);
		nodes[i].applyForce(repulsionForce * 1);
	}

	// Update Position only once all Velocity caches are calculated
	for (std::size_t i = 0; i != nodes.size(); ++i)
	{
		nodes[i].update();
	}
}

void DiffLine::addNode(Node node) {
	octree->insert(ofVec3f(node.position.x, node.position.y, node.position.z)); // insert into octree
	nodes.push_back(node);
}

void DiffLine::addNodeAt(int i, Node node) {
	octree->insert(ofVec3f(node.position.x, node.position.y, node.position.z)); // insert into octree
	std::vector<Node>::iterator it = nodes.begin() + i;
	nodes.insert(it, node);
}

// Helper Function 
int DiffLine::idxFix(int i) {
	int c = nodes.size();
	if (i < 0) { return c - 1; }
	else { return i % c; }
}

