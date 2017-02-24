#include "BarnesHutTree.h"

BarnesHutTree::BarnesHutTree(Quad * q)
{
	this->quad = q;
	this->body = nullptr;
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

void BarnesHutTree::insert(Body *b)
{
	if (this->body == nullptr) {
		this->totalMass = b->mass;
		this->cmx = b->px;
		this->cmy = b->py;
		this->body = b;
	}
	else if (this->isExternal(this) == false) {
		double tMass = this->totalMass + b->mass;
		this->cmx = (this->cmx * this->totalMass + b->px* b->mass) / tMass;
		this->cmy = (this->cmy * this->totalMass + b->py* b->mass) / tMass;
		this->totalMass = tMass;
		this->body = placeHolder;

		Quad *northWest = this->quad->NW();
		if (b->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest);
			}
			this->NW->insert(b);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (b->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast);
				}
				this->NE->insert(b);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (b->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast);
					}
					this->SE->insert(b);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (this->SW == nullptr) {
						this->SW = new BarnesHutTree(southWest);
					}
						this->SW->insert(b);
				}
			}
		}
	}
	else if (this->isExternal(this)) {
		Body * c = this->body;
		Quad *northWest = this->quad->NW();
		if (c->in(northWest)) {
			if (this->NW == nullptr) {
				this->NW = new BarnesHutTree(northWest);
			}
			this->NW->insert(c);
		}
		else {
			Quad *northEast = this->quad->NE();
			if (c->in(northEast)) {
				if (this->NE == nullptr) {
					this->NE = new BarnesHutTree(northEast);
				}
				this->NE->insert(c);
			}
			else {
				Quad *southEast = this->quad->SE();
				if (c->in(southEast)) {
					if (this->SE == nullptr) {
						this->SE = new BarnesHutTree(southEast);
					}
					this->SE->insert(c);
				}
				else {
					Quad *southWest = this->quad->SW();
					if (this->SW == nullptr) {
						this->SW = new BarnesHutTree(southWest);
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
	if (this->isExternal(this)) {
		if (this->body != b)
		b->addForce(this->cmx, this->cmy, this->totalMass);
			
	}
	else if (this->quad->getLength() / (this->body->distanceTo(this->cmx, this->cmy, b->px, b->py)) < 2.0) {
		b->addForce(this->cmx, this->cmy, this->totalMass);
	}
	else {
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
