#include "Shader.h"

std::string loadShaderFile(const char *filePath)
{
	std::ifstream shaderFile(filePath);
	std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	return shaderSource;
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	/* Reads in the source code for both shaders */
	std::string vertexSourceString = loadShaderFile(vertexPath);
	const char *vertexSource = vertexSourceString.c_str();
	std::string fragmentSourceString = loadShaderFile(fragmentPath);
	const char *fragmentSource = fragmentSourceString.c_str();

	/* Compile shaders */
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	/* Initialise program and attach shaders */
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	/* Delete shaders */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(program);
}

Shader::~Shader()
{
}

void Shader::use()
{
	glUseProgram(program);
}