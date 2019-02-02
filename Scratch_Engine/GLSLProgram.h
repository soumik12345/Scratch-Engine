#pragma once

#include<string>
#include<GL/glew.h>

using namespace std;

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const string &vertexShaderFilePath, const string &fragmentShaderFilePath);
	void linkShaders();
	void addAttribute(const string &attributeName);
	void use();
	void unuse();

private:
	GLuint _programID, _vertexShaderID, _fragmentShaderID;
	int _numAttributes; // Count number of Attributes

	void compileShader(const string &shaderFilePath, GLuint shaderID);
};