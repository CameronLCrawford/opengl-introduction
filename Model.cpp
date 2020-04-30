#include "Model.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Model::Model(const char *filePath, glm::vec3 colour) : colour(colour)
{
	std::vector<float> vertices;
	std::vector<std::vector<float>> vertexPositions;
	std::vector<std::vector<float>> vertexNormals;

	std::ifstream modelFile(filePath);

	std::string currentLine;
	while (std::getline(modelFile, currentLine))
	{
		std::istringstream lineStream(currentLine);

		std::string lineType;
		lineStream >> lineType;

		/* Unique vertex position */
		if (lineType == "v")
		{
			std::vector<float> vertexPosition(3);
			lineStream >> vertexPosition[0] >> vertexPosition[1] >> vertexPosition[2];
			vertexPositions.push_back(vertexPosition);
		}
		/* Unique vertex normal */
		if (lineType == "vn")
		{
			std::vector<float> vertexNormal(3);
			lineStream >> vertexNormal[0] >> vertexNormal[1] >> vertexNormal[2];
			vertexNormals.push_back(vertexNormal);
		}
		/*
		Face which is in the form p1//n1 p2//n2 p3//n3 where each p denotes the index of that vertex's
		position and each n denotes that vertex's normal index
		*/
		if (lineType == "f")
		{
			std::string indexData;
			std::vector<int> normalIndex;
			for (int i = 0; i < 3; i++)
			{
				lineStream >> indexData;
				std::string currentIndex = "";
				for (int j = 0; j < indexData.size(); j++)
				{
					char currentCharacter = indexData[j];
					if (currentCharacter == '/')
					{
						for (int k = 0; k < 3; k++)
						{
							vertices.push_back(vertexPositions[std::stoi(currentIndex) - 1][k]);
						}
						currentIndex = "";
						j++;
					}
					else
					{
						currentIndex += currentCharacter;
					}
				}
				for (int j = 0; j < 3; j++)
				{
					vertices.push_back(vertexNormals[std::stoi(currentIndex) - 1][j]);
				}
			}
		}
	}

	modelSize = vertices.size() / 6;

	/* Initialises vertex buffer object and vertex array object*/
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

Model::~Model()
{
}

void Model::draw(Shader &shader, glm::mat4 projectionMatrix)
{
	shader.use();
	shader.setMatrixUniform(4, "projectionMatrix", projectionMatrix * modelMatrix);
	shader.setMatrixUniform(4, "modelMatrix", modelMatrix);
	shader.setVectorUniform(3, "objectColour", colour);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, modelSize);
}

void Model::move(glm::vec3 positionDelta)
{
	modelMatrix = glm::translate(modelMatrix, positionDelta);
}

void Model::rotate(float angle, glm::vec3 direction)
{
	modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), direction);
}