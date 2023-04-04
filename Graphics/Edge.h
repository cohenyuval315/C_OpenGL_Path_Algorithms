#pragma once
#define M_PI 3.14159265358979323846
#include <string>
#include "glut.h" 
#include "Vertex.h"


class Vertex;
class Edge
{
private:
	Vertex* v1, * v2; // pointers to vertices in array of 
	GLuint labelTexture = 0;
	double cost;
public:
	Edge();
	~Edge();
	void setVertex1(Vertex* pv) { v1 = pv; }
	void setVertex2(Vertex* pv) { v2 = pv; }
	void setCost(double c) { cost = c; }

	double getCost() { return cost; }
	Vertex* getVertex1() { return v1; }
	Vertex* getVertex2() { return v2; }

	void draw();
	void createLabelTexture();
};


