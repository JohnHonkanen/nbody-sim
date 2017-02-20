#include "Quad.h"

Quad::Quad()
{
}

Quad::Quad(double xmid, double ymid, double length)
{
	this->xmid = xmid;
	this->ymid = ymid;
	this->length = length;
}

Quad::~Quad()
{
}

double Quad::getLength()
{
	return this->length;
}

bool Quad::contains(double xmid, double ymid)
{
	if ((xmid <= this->xmid + this->length / 2.0) && (xmid >= this->xmid - this->length / 2.0) &&
		(ymid <= this->ymid + this->length / 2.0) && (ymid >= this->ymid - this->length / 2.0)) 
	{
		return true;
	}

	return false;
}

Quad *Quad::NW()
{
	Quad* newQuad = new Quad(this->xmid - this->length / 4.0, this->ymid + this->length / 4.0, this->length / 2.0);
	return newQuad;
}

Quad * Quad::NE()
{
	Quad* newQuad = new Quad(this->xmid + this->length / 4.0, this->ymid + this->length / 4.0, this->length / 2.0);
	return newQuad;
}

Quad * Quad::SW()
{
	Quad* newQuad = new Quad(this->xmid - this->length / 4.0, this->ymid - this->length / 4.0, this->length / 2.0);
	return newQuad;
}

Quad * Quad::SE()
{
	Quad* newQuad = new Quad(this->xmid + this->length / 4.0, this->ymid - this->length / 4.0, this->length / 2.0);
	return newQuad;
}