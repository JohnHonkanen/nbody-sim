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

BarnesHutTree::~BarnesHutTree()
{
}

bool BarnesHutTree::isExternal(BarnesHutTree * t)
{
	if((t->NW==nullptr) && (t->NE == nullptr) && (t->SW == nullptr) && (t->SE == nullptr))
		return true;
	return false;
}

void BarnesHutTree::insert(Body *b)
{
	if (this->hasBody == false) {
		this->totalMass = b->mass;
		this->cmx = b->px;
		this->cmy = b->py;
		this->bodies.push_back(b);
		this->hasBody = true;
	}
	else if (this->isExternal(this) == false) {
		double tMass = this->totalMass + b->mass;
		this->cmx = (this->cmx * this->totalMass + b->px* b->mass) / tMass;
		this->cmy = (this->cmy * this->totalMass + b->py* b->mass) / tMass;
		this->totalMass = tMass;
		this->bodies.push_back(b);

		if (depth < MAX_DEPTH) {
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
						this->NE = new BarnesHutTree(northEast, depth + 1);
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
	}
	else if (this->isExternal(this)) {
		Body * c = this->bodies[0];
		if (depth < MAX_DEPTH) {
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
}

void BarnesHutTree::updateForce(Body* b, int &colliding)
{
	if (b == nullptr)
		return;

	if (this->isExternal(this)) {
		for (unsigned int i = 0; i < this->bodies.size(); i++) {
			if (this->bodies[i] != b && this->bodies[i] != nullptr) {
				if (b->checkCollisions(this->bodies[i])) {
					this->bodies[i]->mass += b->mass;
					this->bodies[i]->calculateRadius();
					colliding = 1;
					cout << "colliding";
				}
				else {
					b->addForce(this->bodies[i]->py, this->bodies[i]->py, this->bodies[i]->mass);
				}
				
			}
		}
	}
	else if (this->quad->getLength() / (b->distanceTo(this->cmx, this->cmy, b->px, b->py)) < 2.0) {
		b->addForce(this->cmx, this->cmy, this->totalMass);
	}
	else {
		if (this->NW != nullptr)
			this->NW->updateForce(b, colliding);
		if (this->SW != nullptr)
			this->SW->updateForce(b, colliding);
		if (this->SE != nullptr)
			this->SE->updateForce(b, colliding);
		if (this->NE != nullptr)
			this->NE->updateForce(b, colliding);
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
		delete this->NW;
	if (this->SW != nullptr)
		delete this->SW;
	if (this->SE != nullptr)
		delete this->SE;
	if (this->NE != nullptr)
		delete this->NE;

	delete this->quad;
	delete this;
}
