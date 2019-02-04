#pragma once
#include<GL/glew.h>

struct Vertex {
	
	struct Position {
		float x, y;
	} position;

	struct Color {
		float r, g, b, a;
	} color;

};