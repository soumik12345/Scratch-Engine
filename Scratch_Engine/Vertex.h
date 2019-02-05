#pragma once
#include<GL/glew.h>

struct Position {
	float x, y;
};

struct Color {
	float r, g, b, a;
};

struct Vertex {
	
	Position position;
	Color color;
	
};