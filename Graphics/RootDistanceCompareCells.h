#pragma once
#include "Cell.h"
#include <math.h>

class RootDistanceCompareCells
{
private:
	int start_x;
	int start_y;
	int target_x;
	int target_y;

public:


	RootDistanceCompareCells();
	RootDistanceCompareCells(int start_x, int start_y, int target_x, int target_y);
	~RootDistanceCompareCells();

	void setTarget(int x, int y) { target_x = x; target_y = y; }
	void setStart(int x, int y) { start_x = x; start_y = y; }

	bool operator() (Cell* c1, Cell* c2) {
		return calculateFScore(c1) > calculateFScore(c2);
	}

	double calculateGScore(Cell* c) {
		if (c->getParent() == nullptr) {
			return 0;
		}
		else {
			return calculateGScore(c->getParent()) + 1;
		}
	}

	double heuristicCostEstimate(Cell* c) {
		return _manhattan_distance(c);
	}

	double calculateFScore(Cell* c) {
		double gScore = calculateGScore(c);
		double hScore = heuristicCostEstimate(c);
		return gScore + hScore;
	}

	double _euclidean_distance(Cell* c) {
		int x_distance = target_x - c->getRow();
		int y_distance = target_y - c->getColumn();
		double d = x_distance * x_distance + y_distance * y_distance;
		return sqrt(d);
	}
	double _manhattan_distance(Cell* c) {
		int x_distance = target_x - c->getRow();
		int y_distance = target_y - c->getColumn();
		double d = x_distance  + y_distance;
		if (d < 0) {
			d = d * -1;
		}
		return d;
	}

};


