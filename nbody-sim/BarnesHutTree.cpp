#include "BarnesHutTree.h"

BarnesHutTree::BarnesHutTree(Quad * q, unsigned int depth)
{
	this->quad = q;
	this->NW = nullptr;
	this->NE = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
	this->depth = depth;
}

BarnesHutTree::BarnesHutTree(Quad * q, vector<Body*> bodies, unsigned int depth)
{
	this->quad = q;
	this->NW = nullptr;
	this->NE = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
	this->depth = 0;
	this->bodies = bodies;
}

BarnesHutTree::~BarnesHutTree()
{
}

void BarnesHutTree::generateChildren()
{
	std::vector<Body*> NWBodies, NEBodies, SWBodies, SEBodies;
	Quad *northWest = this->quad->NW();
	Quad *northEast = this->quad->NE();
	Quad *southEast = this->quad->SE();
	Quad *southWest = this->quad->SW();
	for (unsigned int i = 0; i < bodies.size(); i++)
	{
		if (bodies[i]->in(northWest)) {
			NWBodies.push_back(bodies[i]);
		}
		else {
			if (bodies[i]->in(northEast)) {
				NEBodies.push_back(bodies[i]);
			}
			else {
			
				if (bodies[i]->in(southEast)) {
					SEBodies.push_back(bodies[i]);
				}
				else {
					SWBodies.push_back(bodies[i]);
				}
			}
		}
	}

	this->NW = new BarnesHutTree(northWest, depth + 1);
	this->NW->setUpTree(NWBodies);
	this->NE = new BarnesHutTree(northEast, depth + 1);
	this->NE->setUpTree(NEBodies);
	this->SE = new BarnesHutTree(southEast, depth + 1);
	this->SE->setUpTree(SEBodies);
	this->SW = new BarnesHutTree(southWest, depth + 1);
	this->SW->setUpTree(SWBodies);
}

void BarnesHutTree::setUpTree(vector<Body*> bodies)
{
	this->bodies = bodies;
	this->calculateCenterOfMass();
	if (this->bodies.size() > 1 && this->depth < MAX_DEPTH) {
		this->generateChildren();
		this->hasChildren = true;
	}
}
//Old Code
bool BarnesHutTree::isExternal(BarnesHutTree * t)
{
	if((t->NW==nullptr) && (t->NE == nullptr) && (t->SW == nullptr) && (t->SE == nullptr))
		return true;
	return false;
}
//Old Code to Insert
void BarnesHutTree::insert(Body *b)
{
	if (this->bodies.size() == 0) {
		this->totalMass = b->mass;
		this->cmx = b->px;
		this->cmy = b->py;
		this->bodies.push_back(b);
	}
	else if (this->isExternal(this) == false) {
		this->bodies.push_back(b);
		double tMass = this->totalMass + b->mass;
		this->cmx = (this->cmx * this->totalMass + b->px* b->mass) / tMass;
		this->cmy = (this->cmy * this->totalMass + b->py* b->mass) / tMass;
		this->totalMass = tMass;

		Quad *northWest = this->quad->NW();
		if (b->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest, depth + 1);
			}
			this->NW->insert(b);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (b->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast, depth+1);
				}
				this->NE->insert(b);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (b->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast, depth + 1);
					}
					this->SE->insert(b);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (this->SW == nullptr) {
						this->SW = new BarnesHutTree(southWest, depth + 1);
					}
						this->SW->insert(b);
				}
			}
		}
	}
	else if (this->isExternal(this)) {
		Body * c = this->bodies[0];
		Quad *northWest = this->quad->NW();
		if (c->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest, depth + 1);
			}
			this->NW->insert(c);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (c->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast, depth + 1);
				}
				this->NE->insert(c);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (c->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast, depth + 1);
					}
					this->SE->insert(c);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (this->SW == nullptr) {
						this->SW = new BarnesHutTree(southWest, depth + 1);
					}
					this->SW->insert(c);
					
				}
			}
		}
		this->insert(b);
	}
}

void BarnesHutTree::updateForce(Body* b)
{
	if (!this->hasChildren) {
		cout << this->bodies.size() << endl;
		for (unsigned int i = 0; i < this->bodies.size(); i++) {
			if (this->bodies[i] != b)
				b->addForce(this->bodies[i]->px, this->bodies[i]->py, this->bodies[i]->mass);
		}			
	}
	else if (this->quad->getLength() / (b->distanceTo(this->cmx, this->cmy, b->px, b->py)) < 1.0) {
		b->addForce(this->cmx, this->cmy, this->totalMass);
	}
	else if(this->hasChildren){
		if (this->NW != nullptr)
			this->NW->updateForce(b);
		if (this->SW != nullptr)
			this->SW->updateForce(b);
		if (this->SE != nullptr)
			this->SE->updateForce(b);
		if (this->NE != nullptr)
			this->NE->updateForce(b);
	}
}

void BarnesHutTree::draw()
{
	this->quad->draw();
	if (this->NW != nullptr)
		this->NW->draw();
	if (this->SW != nullptr)
		this->SW->draw();
	if (this->SE != nullptr)
		this->SE->draw();
	if (this->NE != nullptr)
		this->NE->draw();
}

void BarnesHutTree::clearTree()
{
	this->bodies.clear();
	if (this->NW != nullptr)
		this->NW->clearTree();
	if (this->SW != nullptr)
		this->SW->clearTree();
	if (this->SE != nullptr)
		this->SE->clearTree();
	if (this->NE != nullptr)
		this->NE->clearTree();

	//Clear Child
	delete this->NE;
	delete this->NW;
	delete this->SE;
	delete this->SW;
}
// Center of Mass Calculation for Particles
void BarnesHutTree::calculateCenterOfMass()
{
	double mass = 0;
	double cx = 0;
	double cy = 0;

	for (unsigned int i = 0; i < bodies.size(); i++) {
		mass += bodies[i]->mass;
		cx += bodies[i]->px*bodies[i]->mass;
		cy += bodies[i]->py*bodies[i]->mass;
	}

	this->cmx = cx / mass;
	this->cmx = cy / mass;
	this->totalMass = mass;
}
