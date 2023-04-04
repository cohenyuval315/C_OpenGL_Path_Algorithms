#pragma once
#include "Definitions.h"

class Node
{
private:
	int board[BSZ][BSZ];
	Node* parent;
	int empty_row, empty_col;
	double g, h, f;
public:
	Node();
	Node(Node* pn, int direction);
	~Node();
	void draw();
	bool isAdjacent(int row, int col);
	void exchangeCells(int row, int col);
	void computeH();
	void computeF() { f = g + h; }
	int ManhattanDistance(int row, int col);
	void setG(int value) { g = value; }

	double getF() { return f; }

	bool operator == (const Node& other);
	int getEmptyRow() { return empty_row; }
	int getEmptyCol() { return empty_col; }
};

