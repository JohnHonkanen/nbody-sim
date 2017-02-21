#include "BarnesHutTree.h"

BarnesHutTree::BarnesHutTree(Quad * q)
{
	this->quad = q;
	this->particle = nullptr;
	this->NW = nullptr;
	this->NE = nullptr;
	this->SW = nullptr;
	this->SE = nullptr;
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

void BarnesHutTree::insert(Particle * p)
{
	if (this->particle == nullptr) {
		this->particle = p;
	}
	else if (this->isExternal(this) == false) {
		this->totalMass = this->particle->mass + p->mass;
		this->centerPosition = ((this->particle->position*0.5) + (p->position*0.5));

		Quad *northWest = this->quad->NW();
		if (p->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest);
			}
			this->NW->insert(p);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (p->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast);
				}
				this->NE->insert(p);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (p->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast);
					}
					this->SE->insert(p);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (p->in(southWest)) {
						if (this->SW == nullptr) {
							this->SW = new BarnesHutTree(southWest);
						}
						this->SW->insert(p);
					}
				}
			}
		}
	}
	else if (this->isExternal(this)) {
		Particle * p2 = this->particle;
		Quad *northWest = this->quad->NW();
		if (p2->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest);
			}
			this->NW->insert(p2);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (p2->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast);
				}
				this->NE->insert(p2);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (p2->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast);
					}
					this->SE->insert(p2);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (this->SW == nullptr) {
						this->SW = new BarnesHutTree(southWest);
					}
					this->SW->insert(p2);
					
				}
			}
		}
		this->insert(p);
	}
}

void BarnesHutTree::updateForce(Particle * p)
{
	if (this->isExternal(this)) {
			p->addForce(this->centerPosition, this->totalMass);
	}
	else if (this->quad->getLength() / (this->particle->distanceTo(p)) < 2) {
			p->addForce(this->particle);
	}
	else {
		if (this->NW != nullptr)
			this->NW->updateForce(p);
		if (this->SW != nullptr)
			this->SW->updateForce(p);
		if (this->SE != nullptr)
			this->SE->updateForce(p);
		if (this->NE != nullptr)
			this->NE->updateForce(p);
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
