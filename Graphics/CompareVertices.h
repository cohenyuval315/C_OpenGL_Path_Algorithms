#pragma once
#include "Vertex.h"

class CompareVertices
{
public:
	CompareVertices();
	~CompareVertices();

	bool operator() (Vertex* v1, Vertex* v2) {
		return v1->getG() > v2->getG();
	}
};

