
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
	subdivided = false;

}
Octree::~Octree() {

}

void Octree::reset()
{
	if(subdivided)
	{
		for (int i = 0; i < 8; ++i)
		{
			children[i]->reset();
			children[i] = nullptr;
		}
		subdivided = false;
	}
}

bool Octree::insert(std::shared_ptr<Particle> p)
{
	if (!isInBounds(p->pos))
	{
		return false;
	}
	if ((particles.size() < capacity) && subdivided == false)
	{
		particles.push_back(p);
		return true;
	}
	if (subdivided == false)
	{
		subdivide(pos);
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (children[i]->insert(p))
		{
			return true;
		}
	}
}

void Octree::subdivide(glm::vec3 p) {

	// ##### Subdivide the tree

	float s2 = size / 2; 
	float s4 = size / 4; 
	
	children[0] = std::make_unique<Octree>(glm::vec3(p.x - s4, p.y - s4, p.z + s4), s2, false); // TopFrontLeft
	children[1] = std::make_unique<Octree>(glm::vec3(p.x + s4, p.y - s4, p.z + s4), s2, false); // TopFrontRight
	children[2] = std::make_unique<Octree>(glm::vec3(p.x - s4, p.y - s4, p.z - s4), s2, false); // TopBackLeft
	children[3] = std::make_unique<Octree>(glm::vec3(p.x + s4, p.y - s4, p.z - s4), s2, false); // TopBackRight
	children[4] = std::make_unique<Octree>(glm::vec3(p.x - s4, p.y + s4, p.z + s4), s2, false); // BotFrontLeft
	children[5] = std::make_unique<Octree>(glm::vec3(p.x + s4, p.y + s4, p.z + s4), s2, false); // BotFrontRight
	children[6] = std::make_unique<Octree>(glm::vec3(p.x - s4, p.y + s4, p.z - s4), s2, false); // BotBackLeft
	children[7] = std::make_unique<Octree>(glm::vec3(p.x + s4, p.y + s4, p.z - s4), s2, false); // BotBackRight
	
	subdivided = true;

	// i find it easier te recall insert here
	// this is to make sure there are no branches containing data, only leaves
	for (size_t i = 0; i < particles.size(); i++)
	{
		insert(particles[i]);
	}
}

bool Octree::isInBounds(glm::vec3 n)
{
	bool betweenX = (pos.x - size / 2 <= n.x && n.x <= pos.x + size / 2); // 312 <= 555 && 555 <= 712
	bool betweenY = (pos.y - size / 2 <= n.y && n.y <= pos.y + size / 2); // 184 <= 412 && 412 <= 784
	bool betweenZ = (pos.z - size / 2 <= n.z && n.z <= pos.z + size / 2); // -200 <= 050 && 050 <= 200

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
		if (particles.size() == 0){ofSetColor(c1);}
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
		numPoints += particles.size();
	}
	return numPoints;
}

vector<std::shared_ptr<Particle>> Octree::queryInRadius(std::shared_ptr<Particle> c, float r)
{
	vector<std::shared_ptr<Particle>> found;

	if (!intersects(c, r))
	{
		return found;
	}
	for (size_t i = 0; i < particles.size(); i++) // MAYBE ONLY DO THIS IF IT IS A LEAF SO ITS MORE OPTIMIZED
	{
		if (inRadius(c, r, particles[i]))
		{
			found.push_back(particles[i]);
		}
	}
	if (subdivided)
	{
		for (size_t i = 0; i < 8; i++)
		{
			vector<std::shared_ptr<Particle>> found2 = children[i]->queryInRadius(c, r);
			found.insert(found.end(), found2.begin(), found2.end());
		}
	}
	return found;
}

bool Octree::intersects(std::shared_ptr<Particle> c, float r)
{
	float s2 = size / 2;
	glm::vec3 c1 = glm::vec3(pos.x - s2, pos.y - s2, pos.z - s2);// corner 1 of box
	glm::vec3 c2 = glm::vec3(pos.x + s2, pos.y + s2, pos.z + s2);// corner 2 of box
	float d = r * r;
	if (c->pos.x < c1.x) d -= pow((c->pos.x - c1.x),2);
	else if (c->pos.x > c2.x) d -= pow((c->pos.x - c2.x),2);
	if (c->pos.y < c1.y) d -= pow((c->pos.y - c1.y),2);
	else if (c->pos.y > c2.y) d -= pow((c->pos.y - c2.y),2);
	if (c->pos.z < c1.z) d -= pow((c->pos.z - c1.z),2);
	else if (c->pos.z > c2.z) d -= pow((c->pos.z - c2.z),2);
	return d > 0;
}

bool Octree::inRadius(std::shared_ptr<Particle> c, float r, std::shared_ptr<Particle> p)
{
	float x = pow((p->pos.x - c->pos.x), 2);
	float y = pow((p->pos.y - c->pos.y), 2);
	float z = pow((p->pos.z - c->pos.z), 2);
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