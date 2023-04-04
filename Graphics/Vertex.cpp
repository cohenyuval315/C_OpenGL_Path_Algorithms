#include "Vertex.h"
#include "glut.h"



Vertex::Vertex()
{
	color = WHITE;
	parent = nullptr;
}


Vertex::~Vertex()
{
}

void Vertex::draw()
{
	double offset = 0.5;

	switch (color) {
	case WHITE:
		glColor3d(1, 1, 1);
		break;
	case BLACK:
		glColor3d(0.7, 1, 0.7);
		break;
	case GRAY:
		glColor3d(1, 0.7, 0);
		break;
	case WHITE_TARGET:
	case GRAY_TARGET:
		glColor3d(1, 0, 0);
		break;
	case PATH:
		glColor3d(0.8, 0, 1);
		break;
	case START:
		glColor3d(0.5, 0.5, 1);
		break;

	}

	glBegin(GL_POLYGON);
	glVertex2d(x - offset, y);
	glVertex2d(x, y + offset);
	glVertex2d(x + offset, y);
	glVertex2d(x, y - offset);
	glEnd();
	// frame
	glColor3d(0, 0, 0); // black
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - offset, y);
	glVertex2d(x, y + offset);
	glVertex2d(x + offset, y);
	glVertex2d(x, y - offset);
	glEnd();
}
