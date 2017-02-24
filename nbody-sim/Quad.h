#pragma once
#include <iostream>
#include <GL\glew.h>
class Quad
{
public:
	Quad();
	Quad(double xmid, double ymid, double length);
	virtual ~Quad();
	double getLength();
	bool contains(double xmid, double ymid);
	Quad *NW();
	Quad *NE();
	Quad *SW();
	Quad *SE();
	void draw();

private:
	double xmid;
	double ymid;
	double length;


};