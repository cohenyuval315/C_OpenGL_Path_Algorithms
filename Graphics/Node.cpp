#include "Node.h"
#include "glut.h"


Node::Node()
{
	int i, j;

	for (i = 0; i < BSZ; i++)
		for (j = 0; j < BSZ; j++)
			board[i][j] = i * BSZ + j + 1;

	board[BSZ - 1][BSZ - 1] = 0;
	empty_row = BSZ - 1;
	empty_col = BSZ - 1;
	parent = nullptr;
	g = 0;
	computeH();
	computeF();
}

Node::Node(Node* pn, int direction)
{
	int i, j;

	for (i = 0; i < BSZ; i++)
		for (j = 0; j < BSZ; j++)
			board[i][j] = pn->board[i][j];
	switch (direction)
	{
	case UP:
		exchangeCells(pn->empty_row - 1, pn->empty_col);
		break;
	case DOWN:
		exchangeCells(pn->empty_row + 1, pn->empty_col);
		break;
	case LEFT:
		exchangeCells(pn->empty_row, pn->empty_col - 1);
		break;
	case RIGHT:
		exchangeCells(pn->empty_row, pn->empty_col + 1);
		break;
	}
	g = pn->g + 1;
	computeH();
	computeF();

}


Node::~Node()
{
}

void Node::draw()
{
	int i, j;
	for (i = 0;i < BSZ;i++)
		for (j = 0; j < BSZ; j++)
		{
			glColor3d(0.7, 0.7, 0.7);
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();

			glColor3d(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();

			// write the number
			if (board[i][j] > 0)
			{
				glColor3d(0, 0, 0);
				if (board[i][j] >= 10)
				{
					glRasterPos2d(j + 0.4, i + 0.5);
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');

				}
				glRasterPos2d(j + 0.5, i + 0.5);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + board[i][j] % 10);
			}
		}
}

bool Node::isAdjacent(int row, int col)
{

	return (abs(empty_row - row) == 1 && abs(empty_col - col) == 0) ||
		(abs(empty_row - row) == 0 && abs(empty_col - col) == 1);
}

void Node::exchangeCells(int row, int col)
{
	board[empty_row][empty_col] = board[row][col];
	board[row][col] = 0;
	empty_row = row;
	empty_col = col;
}

void Node::computeH()
{
	int sum = 0;
	int i, j;
	for (i = 0; i < BSZ; i++)
		for (j = 0; j < BSZ; j++)
			sum += ManhattanDistance(i, j);
	h = sum;
}

int Node::ManhattanDistance(int row, int col)
{
	int value = board[row][col];
	int intended_row = (value - 1) / BSZ;
	int intended_col = (value - 1) % BSZ;
	return abs(row - intended_row) + abs(col - intended_col);
}

bool Node::operator==(const Node& other)
{
	int i, j;
	for (i = 0;i < BSZ;i++)
		for (j = 0;j < BSZ;j++)
			if (board[i][j] != other.board[i][j])	return false;

	return true;
}
