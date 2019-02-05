#include "Primitives.h"
#include<GL/glew.h>
#include<cmath>

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	glEnableClientState(GL_COLOR_ARRAY);
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
	glEnd();
}

void drawDDALine(float x1, float y1, float x2, float y2) {
	glEnableClientState(GL_COLOR_ARRAY);
	glColor3f(1.0f, 0.0f, 0.0f);

	GLfloat dy = y2 - y1, dx = x2 - x1, steps, x_inc, y_inc;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	
	glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		for (int i = 0; i < steps; i++) {
			x1 += (x_inc / 800);
			y1 += (y_inc / 600);
			glVertex2f(x1, y1);
		}
	glEnd();
}