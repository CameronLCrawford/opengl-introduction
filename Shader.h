#pragma once

#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	enum SCALAR_TYPE
	{
		BOOL,
		INT,
		FLOAT
	};

	Shader(const char*, const char*);
	~Shader();

	void use();

	template<typename T>
	void setScalarUniform(unsigned int, const char *, T);

	template<typename T>
	void setVectorUniform(unsigned int, const char *, T);

	template<typename T>
	void setMatrixUniform(unsigned int, const char *, T);

private:
	unsigned int program;
};

template<typename T>
void Shader::setScalarUniform(unsigned int scalarType, const char *uniformName, T uniformData)
{
	switch (scalarType)
	{
	case BOOL:
		glUniform1i(glGetUniformLocation(program, uniformName), (int)uniformData);
		break;
	case INT:
		glUniform1i(glGetUniformLocation(program, uniformName), uniformData);
		break;
	case FLOAT:
		glUniform1f(glGetUniformLocation(program, uniformName), uniformData);
		break;
	}
}

template<typename T>
void Shader::setVectorUniform(unsigned int dimensions, const char *uniformName, T uniformData)
{
	switch (dimensions)
	{
	case 2:
		glUniform2fv(glGetUniformLocation(program, uniformName), 1, glm::value_ptr(uniformData));
		break;
	case 3:
		glUniform3fv(glGetUniformLocation(program, uniformName), 1, glm::value_ptr(uniformData));
		break;
	case 4:
		glUniform4fv(glGetUniformLocation(program, uniformName), 1, glm::value_ptr(uniformData));
		break;
	}
}

template<typename T>
void Shader::setMatrixUniform(unsigned int dimensions, const char *uniformName, T uniformData)
{
	switch (dimensions)
	{
	case 2:
		glUniformMatrix2fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, glm::value_ptr(uniformData));
		break;
	case 3:
		glUniformMatrix3fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, glm::value_ptr(uniformData));
		break;
	case 4:
		glUniformMatrix4fv(glGetUniformLocation(program, uniformName), 1, GL_FALSE, glm::value_ptr(uniformData));
		break;
	}
}