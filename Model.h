#pragma once
#include <glm/glm.hpp>
#include "Shader.h"

class Model
{
public:
	Model(const char *, glm::vec3);
	~Model();

	void draw(Shader &, glm::mat4);

	void move(glm::vec3);
	void rotate(float, glm::vec3);

private:
	unsigned int modelSize;
	unsigned int vertexBuffer;
	unsigned int vertexArray;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	glm::vec3 colour;
};

