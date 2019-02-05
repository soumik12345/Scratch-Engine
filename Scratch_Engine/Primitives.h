#pragma once

#include<GL/glew.h>
#define ROUND(a) ((int)(a + 0.5))

using namespace std;

extern void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
extern void drawDDALine(float x1, float y1, float x2, float y2);