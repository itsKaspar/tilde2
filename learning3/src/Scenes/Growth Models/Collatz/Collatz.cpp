
// ###### Growth Model Studies
// ###### Collatz Conjecture
// ###### Kaspar Ravel - 2020

#include "Collatz.h"

void Collatz::reset() {

}

ofParameterGroup Collatz::gui() {
	params.setName("Collatz Conjecture");
	params.add(isCentered.set("Centered", true));
	params.add(is3D.set("3D", false));
	return params;
}

void Collatz::setup() {
	iter = 0;
}

void Collatz::update() {

	//iter = iter + (int) ofRandom(0,6);
	iter++;
	int n = iter;
	list <int> sequence;

	while (n != 1)
	{
		sequence.push_front(n);
		n = collatz(n);
	}
	sequence.push_front(1);

	// set root

	glm::vec3 rootPos(0, -ofGetHeight() / 2, 0);
	glm::vec3 rootDir(0, 1, 0);
	CollatzBranch root = CollatzBranch(rootPos, rootDir);
	branches.push_back(root);
	CollatzBranch current = root;

	float angle = PI / 32;
	float r = 0.1;

	// now iterate through the list

	for (int const& i : sequence) {

		if (i % 2 == 0)
		{
			//CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, -angle, glm::vec3(ofRandom(0, r),ofRandom(0,r), ofRandom(0, r))), current);
			CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, -angle, glm::vec3(0,0, 1)), current);
			branches.push_back(newBranch);
			current = newBranch;
		}
		else
		{
			CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, angle, glm::vec3(1, 0, 0)), current);
			if (i % 3 == 0) // special rule
			{
				CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, angle, glm::vec3(1, 0, 0)), current);
			}
			else
			{
				CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, angle, glm::vec3(0, 0, 1)), current);
			}
			//CollatzBranch newBranch = CollatzBranch(glm::rotate(current.dir, angle, glm::vec3(ofRandom(0, r), ofRandom(0, r), ofRandom(0, r))), current);
			branches.push_back(newBranch);
			current = newBranch;
		}
	}

	sequence.clear();
}

void Collatz::draw() {

	for (size_t i = 0; i < branches.size(); i++)
	{
		branches[i].draw(c2, opacity);
		//branches[i].debugDraw();
	}

}

int Collatz::collatz(int n)
{
	if (n % 2 == 0) // even
	{
		return n / 2;
	}
	else // odd
	{
		return (n * 3 + 1) / 2;
	}
}



