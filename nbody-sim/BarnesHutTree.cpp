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
		this->particle = p->add(this->particle, p);
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
		if (this->particle != p) {
			p->addForce(this->particle);
		}
		else if (this->quad->getLength() / (this->particle->distanceTo(p)) < 2) {
			p->addForce(this->particle);
		}
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
