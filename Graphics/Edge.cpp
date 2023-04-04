

#include "Edge.h"
#include "glut.h"



Edge::Edge()
{
}


Edge::~Edge()
{
}

void Edge::draw()
{
	if (v1->getColor() == PATH && v2->getColor() == PATH)
	{
		glLineWidth(3);
		glColor3d(1, 0, 0);
	}
	else 	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(v1->getX(), v1->getY());
	glVertex2d(v2->getX(), v2->getY());
	glEnd();
	glLineWidth(1);

	int draw_middle_label = 0;

	if (draw_middle_label == 1) {
		// Create the label texture if it doesn't exist
		if (labelTexture == 0)
		{
			createLabelTexture();
		}


		// Calculate the label position and angle
		double x = (v1->getX() + v2->getX()) / 2;
		double y = (v1->getY() + v2->getY()) / 2;
		double angle = atan2(v2->getY() - v1->getY(), v2->getX() - v1->getX()) * 180 / M_PI;

		// Save the current modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		// Translate and rotate to the label position and angle
		glTranslated(x, y, 0);
		glRotated(angle, 0, 0, 1);

		// Bind the label texture and draw a quad
		glBindTexture(GL_TEXTURE_2D, labelTexture);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2d(-0.5, -0.5);
		glTexCoord2d(1, 0); glVertex2d(0.5, -0.5);
		glTexCoord2d(1, 1); glVertex2d(0.5, 0.5);
		glTexCoord2d(0, 1); glVertex2d(-0.5, 0.5);
		glEnd();
		// Restore the modelview matrix
		glPopMatrix();
	}


}

void Edge::createLabelTexture()
{
	// Set the text color and background color
	const GLubyte textColor[3] = { 0, 0, 0 };
	const GLubyte bgColor[3] = { 255, 255, 255 };

	// Set the font and text size
	void* font = GLUT_BITMAP_HELVETICA_12;
	int fontHeight = 12;
	int fontWidth = glutBitmapWidth(font, '  ');

	// Calculate the size of the label in pixels
	std::string label = std::to_string(this->getCost());
	int width = fontWidth * label.length();
	int height = fontHeight;

	// Create an image buffer for the label
	GLubyte* image = new GLubyte[width * height * 4];

	// Fill the image buffer with the background color
	for (int i = 0; i < width * height * 4; i += 4)
	{
		image[i] = bgColor[0];
		image[i + 1] = bgColor[1];
		image[i + 2] = bgColor[2];
		image[i + 3] = 255; // alpha value
	}

	// Draw the text onto the image buffer
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3ubv(textColor);
	glRasterPos2i(0, fontHeight);


	for (char c : label)
	{
		glutBitmapCharacter(font, c);
		glBitmap(0, 0, 0, 0, fontWidth, 0, NULL);
	}
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image);


	// Create a texture from the image buffer
	glGenTextures(1, &labelTexture);
	glBindTexture(GL_TEXTURE_2D, labelTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	// Clean up
	delete[] image;
}
