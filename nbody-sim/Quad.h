#pragma once
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

private:
	double xmid;
	double ymid;
	double length;


};