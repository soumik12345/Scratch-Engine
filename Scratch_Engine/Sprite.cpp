#include "Sprite.h"
#include "Vertex.h"
#include<cstddef>
#include<cstdio>
#include<iostream>

using namespace std;

Sprite::Sprite() {
	_vboID = 0;
}

Sprite::~Sprite() {
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[4];
	
	vertexData[1].position.x = x + width;
	vertexData[1].position.y = y + height;
	

	vertexData[0].position.x = x;
	vertexData[0].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	vertexData[3].position.x = x + width;
	vertexData[3].position.y = y;


	for (int i = 0; i < 4; i++) {
		vertexData[i].color.r = 1.0f;
		vertexData[i].color.g = 0;
		vertexData[i].color.b = 1.0f;
		vertexData[i].color.a = 1.0f;
	}

	vertexData[1].color.r = 0.0f;
	vertexData[1].color.g = 0.0f;
	vertexData[1].color.b = 1.0f;
	vertexData[1].color.a = 1.0f;

	/*
	vertexData[4].color.r = 0.0f;
	vertexData[4].color.g = 1.0f;
	vertexData[4].color.b = 0.0f;
	vertexData[4].color.a = 1.0f;
	*/

	vertexData[3].color.r = 0.0f;
	vertexData[3].color.g = 1.0f;
	vertexData[3].color.b = 0.0f;
	vertexData[3].color.a = 1.0f;

	glBindBuffer(GL_ARRAY_BUFFER, _vboID); // Bind Vertex Buffer
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind Vertex Buffer
	
	//glEnable(GL_CULL_FACE);
}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);


	// Position Attribute Pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// Color Attribute Pointer
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	

	//glDisableVertexAttribArray(0);
	
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}