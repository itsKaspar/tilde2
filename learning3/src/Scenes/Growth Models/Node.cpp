#include "Node.h"

Node::Node(glm::vec3 p) {
	position = p;
	maxForce = 0.1;
	maxEdgeLen = 10;
}

void Node::update() {
	position += velocity;
	velocity = glm::vec3(0, 0, 0);
}

void Node::debugDraw()
{
	ofSetColor(255, 0, 0, 255);
	ofDrawCircle(position.x, position.y, 3);
	ofSetColor(255, 255, 255, 255);
}

void Node::applyForce(glm::vec3 force) {
	velocity += force;
	if (glm::length(velocity) > maxForce)
		velocity = glm::normalize(velocity) * maxForce;
}

glm::vec3 Node::attractionForce(glm::vec3 v1, glm::vec3 v2) {
	glm::vec3 attractionForce = v1 - v2; // don't need to divide by two again because we're normalizing;
	attractionForce = glm::normalize(attractionForce);
	return attractionForce;
}

glm::vec3 Node::repulsionForce(vector<glm::vec3> neighbours) {
	glm::vec3 repulsionForce;

	for (glm::vec3 v : neighbours)
	{
		float d = glm::distance(v, position);
		glm::vec3 diff = (position - v) / exp(d);
		repulsionForce += diff;
	}
	//repulsionForce /= neighbours.size(); //dont need to do that anymore because Im normalizing
	repulsionForce = glm::normalize(repulsionForce);
	return repulsionForce;
}

