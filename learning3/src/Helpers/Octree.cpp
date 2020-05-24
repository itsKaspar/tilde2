
// ###### Helper Classes
// ###### Octree Implementation
// ###### Kaspar Ravel - 2020

#include "Octree.h"

Octree::Octree() {
}

Octree::Octree(glm::vec3 p, float s, bool r) {

	pos = p;
	size = s;
	isRoot = r;
	capacity = 1;
	subdivided = false;

}
Octree::~Octree() {
	//for (int i = 0; i < 8; ++i)
	//{
	//	delete children[i];
	//}
}

void Octree::reset()
{
	if(subdivided)
	{
		for (int i = 0; i < 8; ++i)
		{
			children[i]->reset();
			delete children[i];
			children[i] = NULL;
		}
		subdivided = false;
	}
}

bool Octree::insert(glm::vec3 n)
{
	if (!isInBounds(n, *this))
	{
		return false;
	}
	if ((points.size() < capacity) && subdivided == false)
	{
		points.push_back(n);
		return true;
	}
	if (subdivided == false)
	{
		subdivide(pos);
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (children[i]->insert(n))
		{
			return true;
		}
	}
}

void Octree::subdivide(glm::vec3 p) {

	// ##### Subdivide the tree

	float s2 = size / 2; 
	float s4 = size / 4; 
	
	children[0] = new Octree(glm::vec3(p.x - s4, p.y - s4, p.z + s4), s2, false); // TopFrontLeft
	children[1] = new Octree(glm::vec3(p.x + s4, p.y - s4, p.z + s4), s2, false); // TopFrontRight
	children[2] = new Octree(glm::vec3(p.x - s4, p.y - s4, p.z - s4), s2, false); // TopBackLeft
	children[3] = new Octree(glm::vec3(p.x + s4, p.y - s4, p.z - s4), s2, false); // TopBackRight
	children[4] = new Octree(glm::vec3(p.x - s4, p.y + s4, p.z + s4), s2, false); // BotFrontLeft
	children[5] = new Octree(glm::vec3(p.x + s4, p.y + s4, p.z + s4), s2, false); // BotFrontRight
	children[6] = new Octree(glm::vec3(p.x - s4, p.y + s4, p.z - s4), s2, false); // BotBackLeft
	children[7] = new Octree(glm::vec3(p.x + s4, p.y + s4, p.z - s4), s2, false); // BotBackRight
	
	subdivided = true;

	// i fin it easier te recall insert here
	// this is to make sure there are no branches containing data, only leaves
	for (size_t i = 0; i < points.size(); i++)
	{
		insert(points[i]);
	}
}

bool Octree::isInBounds(glm::vec3 n, Octree o)
{
	bool betweenX = (o.pos.x - size / 2 <= n.x && n.x <= o.pos.x + size / 2); // 312 <= 555 && 555 <= 712
	bool betweenY = (o.pos.y - size / 2 <= n.y && n.y <= o.pos.y + size / 2); // 184 <= 412 && 412 <= 784
	bool betweenZ = (o.pos.z - size / 2 <= n.z && n.z <= o.pos.z + size / 2); // -200 <= 050 && 050 <= 200

	return (betweenX && betweenY && betweenZ);
}

void Octree::draw(ofColor c1, ofColor c2) {

	ofNoFill();
	if (subdivided) // ##### Draw Children
	{
		for (size_t i = 0; i < 8; i++)
		{
			children[i]->draw(c2, c1);
		}
	}
	else // ##### Draw Self
	{
		if (points.size() == 0){ofSetColor(c1);}
		else{ofSetColor(c2);}
		ofDrawBox(glm::vec3(pos.x, pos.y, pos.z), size); // draw main box
	}
}

int Octree::getNumPoints() {

	int numPoints = 0;

	if (subdivided)
	{
		for (size_t i = 0; i < 8; i++)
		{
			numPoints += children[i]->getNumPoints();
		}
	}
	else
	{
		numPoints += points.size();
	}
	return numPoints;
}

vector<glm::vec3> Octree::queryInRadius(glm::vec3 c, float r)
{
	vector<glm::vec3> found;

	if (!intersects(c, r))
	{
		return found;
	}
	for (size_t i = 0; i < points.size(); i++) // MAYBE ONLY DO THIS IF IT IS A LEAF SO ITS MORE OPTIMIZED
	{
		if (inRadius(c, r, points[i]))
		{
			found.push_back(points[i]);
		}
	}
	if (subdivided)
	{
		for (size_t i = 0; i < 8; i++)
		{
			vector<glm::vec3> found2 = children[i]->queryInRadius(c, r);
			found.insert(found.end(), found2.begin(), found2.end());
		}
	}
	return found;
}

bool Octree::intersects(glm::vec3 c, float r)
{
	float s2 = size / 2;
	glm::vec3 c1 = glm::vec3(pos.x - s2, pos.y - s2, pos.z - s2);// corner 1 of box
	glm::vec3 c2 = glm::vec3(pos.x + s2, pos.y + s2, pos.z + s2);// corner 2 of box
	float d = r * r;
	if (c.x < c1.x) d -= pow((c.x - c1.x),2);
	else if (c.x > c2.x) d -= pow((c.x - c2.x),2);
	if (c.y < c1.y) d -= pow((c.y - c1.y),2);
	else if (c.y > c2.y) d -= pow((c.y - c2.y),2);
	if (c.z < c1.z) d -= pow((c.z - c1.z),2);
	else if (c.z > c2.z) d -= pow((c.z - c2.z),2);
	return d > 0;
}

bool Octree::inRadius(glm::vec3 c, float r, glm::vec3 p)
{
	float x = pow((p.x - c.x), 2);
	float y = pow((p.y - c.y), 2);
	float z = pow((p.z - c.z), 2);
	float d = x + y + z;
	
	if (d < r*r)
	{
		return true;
	}
	else
	{
		return false;
	}
}