#include "Node.h"

Node::Node(glm::vec3 p) {
	pos = p;
	maxForce = 0.1;
	maxEdgeLen = 10;
}