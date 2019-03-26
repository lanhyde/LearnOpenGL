#pragma once

#include <stdio.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	void UseShader();
	void ClearShader();

private:
#pragma region Private Fields
	GLuint shaderID;
	GLuint uniformProjection;
	GLuint uniformModel;
#pragma endregion

#pragma region Private Methods
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
#pragma endregion

};

