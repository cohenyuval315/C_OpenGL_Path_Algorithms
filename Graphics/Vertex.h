#pragma once
#include "Edge.h"
#include <vector>
#include "Definitions.h"
using namespace std;

class Edge;
class Vertex
{
private:
	int x, y; // place in space
	int index; // index of this Vertex in array of vertices
	int color;
	Vertex* parent;
	vector <Edge*> outgoing;
	double g; // sum of costs along path from START
public:
	Vertex();
	~Vertex();
	void setX(int value) { x = value; }
	void setY(int value) { y = value; }
	void setColor(int c) { color = c; }
	void setG(double value) { g = value; }
	void setParent(Vertex* p) { parent = p; }
	void addOutgoingEdge(Edge* e) { outgoing.push_back(e); }

	void draw();
	int getX() { return x; }
	int getY() { return y; }
	double getG() { return g; }
	int getColor() { return color; }
	vector<Edge*> getOutgoing() { return outgoing; }
	Vertex* getParent() { return parent; }
};

