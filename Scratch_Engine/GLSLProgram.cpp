#include "GLSLProgram.h"
#include "Errors.h"
#include<string>
#include<fstream>
#include<vector>

using namespace std;


GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), _fragmentShaderID(0), _numAttributes(0) {

}


GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compileShaders(const string &vertexShaderFilePath, const string &fragmentShaderFilePath) {

	_programID = glCreateProgram();
	
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (_vertexShaderID == 0) {
		fatalError("Failed to create Vertex Shader");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (_fragmentShaderID == 0) {
		fatalError("Failed to create Fragment Shader");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}

// Links the Shaders together into a program to get a program object.
void GLSLProgram::linkShaders() {
	
	// Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	// Link our program
	glLinkProgram(_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE) {
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(_programID);
		// Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		printf("%s\n", &(errorLog[0]));
		fatalError("Filed to sha Shaders");
	}

	// Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);

	// Always delete shaders after a successful link.
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const string &attributeName) {
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++)
		glEnableVertexAttribArray(i);
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++)
		glDisableVertexAttribArray(i);
}

// Compiles a shader from source
void GLSLProgram::compileShader(const string &shaderFilePath, GLuint shaderID) {
	
	// Reading Vertex Shader File

	ifstream vertexFile(shaderFilePath);
	if (vertexFile.fail()) {
		fatalError("Failed to open " + shaderFilePath);
		perror(shaderFilePath.c_str());
	}

	string fileContents = "", line;

	while (getline(vertexFile, line))
		fileContents += line + "\n";

	vertexFile.close();

	// Completed Reading Vertex Shader File


	// Compiling Source for Vertex Shader

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);

	glCompileShader(shaderID);

	// Checking if the compilation of Shader source was succes or not
	GLint success = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(_vertexShaderID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shaderID); // Don't leak the shader.

		printf("%s\n", &(errorLog[0]));
		fatalError("Filed to Compile Shader from source " + shaderFilePath);
	}

	// Done Compilation of Vertex Shader Source
}