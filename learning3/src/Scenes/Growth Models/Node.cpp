#include "Node.h"

Node::Node(float x, float y, float z) {
	position.set(x, y, z);
	maxForce = 0.1;
	maxEdgeLen = 10;
}

void Node::update() {
	position += velocity;
	velocity.set(0, 0, 0);
}

void Node::debugDraw()
{
	ofSetColor(255, 0, 0, 255);
	ofDrawCircle(position.x, position.y, 3);
	ofSetColor(255, 255, 255, 255);
}

void Node::applyForce(ofVec3f force) {
	velocity += force;
	velocity = velocity.getLimited(maxForce);
}

ofVec3f Node::attractionForce(ofVec3f v1, ofVec3f v2) {
	ofVec3f attractionForce = v1 - v2; // don't need to divide by two again because we're normalizing;
	attractionForce.normalize();
	return attractionForce;
}

ofVec3f Node::repulsionForce(vector<ofVec3f> neighbours) {
	ofVec3f repulsionForce;

	for (ofVec3f v : neighbours)
	{
		float d = v.distance(position);
		ofVec3f diff = (position - v) / exp(d);
		repulsionForce += diff;
	}
	//repulsionForce /= neighbours.size(); //dont need to do that anymore because Im normalizing
	repulsionForce.normalize();
	return repulsionForce;
}

